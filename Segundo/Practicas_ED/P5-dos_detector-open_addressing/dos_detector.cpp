/**
 * @file dos_detector.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include "dos_detector.hpp"
#include "hash_table_imp.hpp"

/** @brief Each second, this algorithm scan log to see if some address must be banned.
 * @arg log is the system's log.
 * @arg i is the first not processed line in log.
 * @arg j is the last old line out of the temporal processing windown.
 * @pre j<=i<log.size()
*/
static void
update_counters(Log& log, size_t &i, size_t& j,
                HashTable<IP,int, IpToInt, LPHash>& counters,
                int max_acc)
{

    // First: Updating (incrementing i) the new remote conections.
    // You can use System() to do the os operations.
    // i.e.: System().time() to get the current time ("now").
    //       System().is_banned() to know if a ip is banned at current time.
    //       System().ban_ip() to ban an ip.
    // Remenber: in this simulated case var 'i' can achieve log.size() value.
    while(i < log.size() && log[i].time < System().time())
    {
        if (System().is_banned(log[i].ip))
        {
            // This is necessary because this is a simulated system.
            // In an actual system, a banned ip will be blocked by the firewall so
            // this banned ip shouldn't appear in the log at this time.
            // We reset the log entry's ip to 0.0.0.0 to mark this situation
            // for the next step.
            log[i].ip = IP(0,0,0,0);
        }
        else
        {
            //TODO:
            //Update the counter associated to the ip. If it does not exist,
            //create a new counter for it.
            //Remenber: if the udpated counter is great or equal than max_acc
            //          the ip must be banned for 60 seconds.
            if(counters.find(log[i].ip)){
                int new_value=counters.get_value();
                new_value++;
                counters.set_value(new_value);
                if(max_acc<=new_value){
                    System().ban_ip(log[i].ip, 60);
                }
            }
            else if(!counters.find(log[i].ip)){
                auto new_key=log[i].ip;
                counters.insert(new_key,1);
            }

            //
        }

        ++i;
    }

    //Second: remove old accesses (incrementing j).
    //We use a 60 seconds window time.
    while(j < log.size() && ((log[j].time + 60) < System().time()))
    {
        if (! (log[j].ip == IP(0,0,0,0)) )
        {
            //TODO:
            //Decrementing the counter associated to the ip by one.
            //Hint: Two things must be true here.
            // - We can find the ip in the table and
            // - its counter must be >0 before decrementing.
            //You should check these things to make sure you are doing
            //   well the work.
            if(counters.find(log[j].ip)){
                int value=counters.get_value();
                value--;
                counters.set_value(value);
            }
            //
        }
        ++j;
    }
}


void dos_detector(Log& log, int max_acc, size_t m)
{
    size_t i=0;
    size_t j=0;
    HashTable<IP, int, IpToInt, LPHash> counters(m, IpToInt::create(),
                                                 LPHash::create(m));

    while(!System().sleep(1))
    {
        update_counters(log, i, j, counters, max_acc);
        std::cout << "Banned ips at time " << System().time() << ": "
                  << System().banned_ips() << std::endl;
        if (j==log.size()) //The log is ended.
            System().kill();
    }
}
