#include "packet_processor.hpp"
#include "queue_imp.hpp"

PacketProcessor::PacketProcessor(size_t size):
    _max_size(size),
    _finish_time()
{}

Response PacketProcessor::process(const Packet &packet)
{
    Response ret (true, 0); //Default is to drop the packet.
    //TODO:
    //First: deque all processed packets at packet time arrival.
    int time=0;
    if(!_finish_time.is_empty()){
        if(packet.arrival_time>=_finish_time.front()){
            _finish_time.deque();
        }
    }
    //Second: Is there any place for this packet in the queue?
    //This packet will be processed after the last paquete will do,
    //and the its finish time will be 'packets's process_time' units after.
    //Remenber that the queue holds the finish processing time for the packets.
    if(_finish_time.size()>=_max_size){
        return ret;
    }
    if(_finish_time.is_empty()){
        time=packet.arrival_time;
    }
    else{
        time=_finish_time.back();
    }
    _finish_time.enque(time+packet.process_time);
    ret.dropped=false;
    ret.start_time=time;
    return ret;
}


/** @brief process the packets and generate a response for each of them.*/
std::vector <Response>
process_packets(const std::vector <Packet> &packets,
                PacketProcessor& p)
{
    std::vector <Response> responses;
    for (size_t i = 0; i < packets.size(); ++i)
    {
        responses.push_back(p.process(packets[i]));
    }
    return responses;
}

/** @brief print the processing start times for the packets.*/
std::ostream&
write_responses(std::ostream &out, const std::vector <Response> &responses)
{
    for (size_t i = 0; i < responses.size(); ++i)
        out << (responses[i].dropped ? -1 : responses[i].start_time)
            << std::endl;
    return out;
}
