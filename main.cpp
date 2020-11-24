#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {

    Transaction *first = new Transaction("VRGO", 12, 02, 2019, true, 150, 10300.14);
    Transaction *second = new Transaction("VRGO", 11, 02, 2019, true, 150, 10300.14);
    Transaction *third = new Transaction("VRGO", 10,01,2020, true, 150,10300.14);
    if (first<second) {
        std::cout<<"first<second"<<std::endl;
    } else {
        std::cout<<"second<first"<<std::endl;
    }
//    std::cout << "r u sure" <<std::endl;
    History trans_history{};
//    std::cout << "r u sure" <<std::endl;
    trans_history.insert(first);
    trans_history.insert(second);
    trans_history.insert(third);
//  trans_history.read_history();


  std::cout << "[Starting history]:" << std::endl;
  trans_history.print();
  trans_history.sort_by_date();

  std::cout << "[Sorted          ]:" << std::endl;
  trans_history.print();

//  trans_history.update_acb_cgl();
//  trans_history.print();

  std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2018) << std::endl;
  std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2019) << std::endl;

  return 0;
}
#endif
