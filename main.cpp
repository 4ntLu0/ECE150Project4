#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;

int main() {

//    Transaction *first = new Transaction("VRGO", 12, 02, 2019, true, 150, 10300.14);
//    Transaction *second = new Transaction("VRGO", 18, 01, 2019, true, 150, 10300.14);
//    Transaction *third = new Transaction("VRGO", 11,01,2019, true, 150,10300.14);
//    Transaction *fourth = new Transaction("VRGO", 18, 10, 2020, true, 150, 10300.14);
//    Transaction *fifth = new Transaction("VRGO", 12, 1, 2020, true, 150, 10300.14);
//    Transaction *sixth = new Transaction("VRGO", 12, 02, 2019, true, 150, 10300.14);
//    if (first<second) {
//        std::cout<<"first<second"<<std::endl;
//    } else {
//        std::cout<<"second<first"<<std::endl;
//    }
//    std::cout << "r u sure" <<std::endl;
    History trans_history{};
//    std::cout << "r u sure" <<std::endl;
//    trans_history.insert(first);
//    trans_history.insert(fourth);
//    trans_history.insert(third);
//    trans_history.insert(second);
//    trans_history.insert(fifth);
//    trans_history.insert(sixth);

//    Transaction *first = new Transaction("VRGO", 10, 01, 2018, true, 150, 10300.140);
//    Transaction *second = new Transaction("VRGO", 24, 02, 2018, true, 85, 7423.050);
//    Transaction *third = new Transaction("VRGO", 8, 8, 2018, true, 43, 3367.760);
//    Transaction *fourth = new Transaction("VRGO", 11, 11, 2018, true, 78, 7028.580);
//    Transaction *fifth = new Transaction("VRGO", 8, 12, 2018, false, 55, 5958.150);
//    Transaction *sixth = new Transaction("VRGO", 22, 12, 2018, false, 80, 2817.600);

//    trans_history.insert(first);
//    trans_history.insert(fourth);
//    trans_history.insert(third);
//    trans_history.insert(second);
//    trans_history.insert(fifth);
//    trans_history.insert(sixth);
    trans_history.read_history();


    std::cout << "[Starting history]:" << std::endl;
    trans_history.print();
    trans_history.sort_by_date();

    std::cout << "[Sorted          ]:" << std::endl;
    trans_history.print();

    trans_history.update_acb_cgl();
    trans_history.print();

    std::cout << "[CGL for 2018    ]: " << trans_history.compute_cgl(2019) << std::endl;
    std::cout << "[CGL for 2019    ]: " << trans_history.compute_cgl(2020) << std::endl;

    return 0;
}

#endif
