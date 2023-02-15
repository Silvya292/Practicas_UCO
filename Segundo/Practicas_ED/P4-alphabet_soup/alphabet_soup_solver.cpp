/**
 * @file alphabet_soup_solver.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "alphabet_soup_solver.hpp"
#include "trie.hpp"

/**
 * @brief scan a cell looking for the next letter of a word.
 * @param row and
 * @param col are the current cell coordinates.
 * @param dy and
 * @param dx are direction vector to follow the next letter.
 * @param soup is the alphabet soup where looking for.
 * @param trie is the current subtrie.
 * @param scan_result save the current chain. Is a pair of <word, cells_coordinates [row,col]>
 *
 */
void
scan_cell(int row, int col, int dy, int dx, AlphabetSoup const& soup,
          Trie::Ref trie, ScanResult & scan_result)
{
    //TODO:
    //ALGORITHM
    //1. If the trie's prefix is a key then
    //   a word is found. Save the key as the first item of the scan_result
    //   pair and return from this level of recursion.
    if(trie->is_key()){
        scan_result.first=trie->prefix();
    }
    //2. Else if there is a sub-trie for the symbol (row,col), there is two cases:
    //2.1.1 (dx==dy==0) The cell (row,col) is the first letter of a word.
    //      If there is a sub-trie whose prefix is this symbol, start a new
    //      recursive scanning of the 3x3 neighborhood from this position
    //      using this sub-trie.
    //2.1.2 (dx!=0 or dy!=0) The cell (row,col) is the next letter of a
    //      started scanning following the direction (dx,dy). If there is a
    //      sub-trie whose prefix is this symbol, continue the scanning
    //      following the direction (dx,dy) recursively.
    //2.2 After recursion comes back, if a word was found (first item of
    //    the scan_result pair != ""), push the current cell's coordinates
    //    (row,col) into the second item of scan_result (the stack of
    //    coordinates).
    else{
        if(row>=0 && row<soup.rows() && col>=0 && col<soup.cols()){
            auto const cell=soup.cell(row,col);
            if(trie->find_symbol(cell)){
                trie=trie->current();
                bool found=false;
                if(dx==0 && dy==0){
                    for(int i=std::max(row-1,0);i<std::min(row+2,soup.rows()) && !found;i++){
                        for(int j=std::max(col-1,0);j<std::min(col+2,soup.cols()) && !found;j++){   
                            if(i!=row || j!=col){
                                scan_cell(i,j,j-col,i-row,soup,trie,scan_result);
                                found=(scan_result.first!="");
                            }
                        }
                    }
                }
                else{
                    scan_cell(row+dx,col+dy,dy,dx,soup,trie,scan_result);
                    found=(scan_result.first!="");
                }
                if(found==true){
                    scan_result.second.push(std::pair<int,int>(row,col));
                }
            }
        }
    }


    //
}

std::vector< ScanResult >
alphabet_soup_solver(AlphabetSoup& soup, std::vector<std::string> const& words)
{
    std::vector< ScanResult > results;
    auto trie = Trie::create();

    //Generate a trie with the words to be found as keys.
    for (size_t i = 0; i<words.size(); ++i)
        trie->insert(words[i]);

    //We scan all the soup to find a first letter of any key.
    for (int row = 0; row < soup.rows(); ++row)
    {
        for (int col = 0; col < soup.cols(); ++col)
        {
            auto scan_result = std::make_pair(std::string(""),
                                              std::stack<std::pair<int,int>>());
            //Scan from this cell. This is the first letter so dx==dy==0.
            scan_cell(row, col, 0, 0, soup, trie, scan_result);
            if (scan_result.first!="")
              //A word was found so save it into the results.
              results.push_back(scan_result);
        }
    }
    return results;
}

