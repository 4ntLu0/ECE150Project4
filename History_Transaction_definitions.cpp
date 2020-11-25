#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//

Transaction::Transaction(std::string ticker_symbol, unsigned int day_date, unsigned int month_date,
                         unsigned int year_date, bool buy_sell_trans, unsigned int number_shares,
                         double trans_amount) {
    symbol = ticker_symbol;
    day = day_date;
    month = month_date;
    year = year_date;
    if (buy_sell_trans) {
        trans_type = "Buy";
    } else {
        trans_type = "Sell";
    }
    shares = number_shares;
    amount = trans_amount;

    trans_id = assigned_trans_id;
    assigned_trans_id++;


}


// Destructor
// TASK 1
//

Transaction::~Transaction() {
    // destructor calls on delete, or on de-allocation of instance?
    // clear dynamically allocated things (p_next?)
//    delete p_next;
    p_next = nullptr;

}


// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<(Transaction const &other) { //this is very important please fix this.
    // how is this supposed to work?
    // find out which transaction happens before the other?


    // if (trans1 < trans2)
    // day = trans1
    // other.day = trans2

    //if (trans2 < trans1)
    // day = trans2
    // other.day = trans1

    //basically the one on the left is the one we have, and the one on the right is other.

    if (this->year < other.year) {
        //the left one is an entire year smaller, there is no contest.
        return true;
    } else if (this->year == other.year) {
        //same year so check month
        if (this->month < other.month) {
            // the left one is a lesser month, so we're automatically good
            return true;
        } else if (this->month == other.month) {
            //same month so check day
//            std::cout<<"samemonth"<<std::endl;
//            std::cout<<this->day<<" "<<other.day<<std::endl;
            if (this->day < other.day) {
                // left day is less!
//                std::cout<<"true"<<std::endl;
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    } else {
        return false;
    }

    return false; //if nothing else has happened then you just return false!
}


// GIVEN
// Member functions to get values.
std::string Transaction::get_symbol() const { return symbol; }

unsigned int Transaction::get_day() const { return day; }

unsigned int Transaction::get_month() const { return month; }

unsigned int Transaction::get_year() const { return year; }

unsigned int Transaction::get_shares() const { return shares; }

double Transaction::get_amount() const { return amount; }

double Transaction::get_acb() const { return acb; }

double Transaction::get_acb_per_share() const { return acb_per_share; }

unsigned int Transaction::get_share_balance() const { return share_balance; }

double Transaction::get_cgl() const { return cgl; }

bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }

unsigned int Transaction::get_trans_id() const { return trans_id; }

Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }

void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }

void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }

void Transaction::set_cgl(double value) { cgl = value; }

void Transaction::set_next(Transaction *p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(4) << get_trans_id() << " "
              << std::setw(4) << get_symbol() << " "
              << std::setw(4) << get_day() << " "
              << std::setw(4) << get_month() << " "
              << std::setw(4) << get_year() << " ";


    if (get_trans_type()) {
        std::cout << "  Buy  ";
    } else { std::cout << "  Sell "; }

    std::cout << std::setw(4) << get_shares() << " "
              << std::setw(10) << get_amount() << " "
              << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
              << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
              << std::setw(10) << std::setprecision(3) << get_cgl()
              << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//

// each transaction is a node of the linked list.
// History is/holds/contains the linked list
/*
 * History
 * p_head --> Transaction
 *            p_next ---------> Transaction
 *                              p_next --------> Transaction etc etc etc ---> nullptr
 *
 *
 */


// Constructor
// TASK 3
//

History::History() {
    p_head = nullptr;
//    p_head->set_next(nullptr);
//    std::cout << "set pointers" << std::endl;
}


// Destructor
// TASK 3
//

History::~History() {
    Transaction *p_temp{p_head};
    if (p_temp != nullptr) {
        while (p_temp->get_next() != nullptr) {
            p_head = p_temp->get_next();
            delete p_temp;
            p_temp = nullptr;
            p_temp = p_head;
        }

        delete p_temp;
        p_temp = nullptr;
        p_head = nullptr;
    }

}


// read_transaction(...): Read the transaction history from file.
// TASK 4
//
void History::read_history() {
    // reads everything from a file and then inserts it into a list!
//    std::cout << "read history prev" << std::endl;
    ece150::open_file(); //opens file so that we can access.
    while (ece150::next_trans_entry()) { // while there is a next line
//        std::cout << "read_history" << std::endl;
        Transaction *new_trans = new Transaction(
                ece150::get_trans_symbol(),
                ece150::get_trans_day(),
                ece150::get_trans_month(),
                ece150::get_trans_year(),
                ece150::get_trans_type(),
                ece150::get_trans_shares(),
                ece150::get_trans_amount()
        );
        insert(new_trans);
    }
    ece150::close_file();

}


// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans) {
    //adds something to the end (not really the end but in the middle lol)
    assert(p_new_trans != nullptr);
    p_new_trans->set_next(nullptr);
    if (p_head == nullptr) {
//        std::cout << "null p_head insert" << std::endl;
//        std::cout << "p_new_trans" << p_new_trans->get_year() << " " << p_new_trans->get_month() << " "
//                  << p_new_trans->get_day() << std::endl;
        p_head = p_new_trans;
        p_head->set_next(nullptr);
//        std::cout << "p_head" << p_head->get_year() << " " << p_head->get_month() << " "
//                  << p_head->get_day() << std::endl;
    } else {
        Transaction *p_temp = p_head;
        while (p_temp != nullptr) {
            if (p_temp->get_next() == nullptr) {
//                std::cout << "p_new_trans" << p_new_trans->get_year() << " " << p_new_trans->get_month() << " "
//                          << p_new_trans->get_day() << "get:next" << p_new_trans->get_next() << std::endl;
                p_temp->set_next(p_new_trans);
                break;
            }
            p_temp = p_temp->get_next();

        }
    }
}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {
    // sort by date and then trans id.
    // sort by rebuilding the entire thing?
    /*
     * step 1: check if list is empty/single node
     * step 2: move first node to new list.
     *     2a: start with local pointer p_sorted
     *     2b: point p_sorted to p_head
     *     2c: move p_head to p_head->get_next();
     *     2d: separate lists by setting first p_next to nullptr
     * step 3: take one node off p_head list
     *     3a: declare another temp pointer and point it to first node in p_head list
     *     3b: move p_head to second node
     *     3c: separate p_temp node by setting p_next to nullptr (on p_temp)
     * step 4: insert p_temp into the p_sorted list
     *  case1: putting at very beginning (change p_sorted)
     *  case2: p_temp goes anywhere else.
     *   4c1a: p_next = p_sorted;
     *   4c1b: p_sorted = p_temp; (move p_sorted to the front)
     *   4c2a: declare another pointer (p_insert=p_sorted)
     *   4c2b: move p_insert until p_insert<p_temp<p_insert->next (or the end).
     *   4c2c: p_temp->set_next(p_insert->get_next()); // basically add in the remap.
     *   4c2d: p_insert->set_next(p_temp); ? ? ?
     * step 5: repeat steps 3/4 until p_head is empty (nullptr).
     * step 6: set p_head to p_sorted;
     */

    if (p_head == nullptr) {
        // 0 nodes
        return;
    } else if (p_head->get_next() == nullptr) {
        // 1 node
        return;
    }
    //else sort everything normally

    Transaction *p_sorted = p_head;
    p_head = p_head->get_next();
    p_sorted->set_next(nullptr);

    while (p_head != nullptr) {
        Transaction *p_temp = p_head;
        p_head = p_head->get_next();
        // insert p_temp into p_sorted.
//        std::cout << "p_temp " << p_temp->get_year() << " " << p_temp->get_month() << " " << p_temp->get_day()
//                  << std::endl;
//        std::cout << "p_sorted " << p_sorted->get_year() << " " << p_sorted->get_month() << " "
//                  << p_sorted->get_day() << std::endl;
        if (*p_temp < *p_sorted) {
            // this means that we have to change p_sorted.
//            std::cout << "ptem<psorted" << std::endl;
            p_temp->set_next(p_sorted);
            p_sorted = p_temp;
        } else {
            Transaction *p_insert = p_sorted;
            while (p_insert != nullptr) {
                // so basically it goes until there is no more after (so like 7-8-9 it will stop at 8 so 9 is counted).
                if ((p_insert->get_next() == nullptr)) {
//                    std::cout << "nullptr" << std::endl;
                    //next one is nullptr (p_temp > all p_insert).
                    p_insert->set_next(p_temp);
                    p_temp->set_next(nullptr);
                    break;
                    // need a case to check if they're the same day.
                } else if (((p_insert->get_year()) == (p_temp->get_year())) &&
                           ((p_insert->get_month()) == (p_temp->get_month())) &&
                           ((p_insert->get_day()) == (p_temp->get_day()))) {
                    // p_insert->get_next() not null and equal.
                    if ((p_insert->get_trans_id())<(p_temp->get_trans_id())){
                        //p insert has the smaller trans ID, therefore must be inserted before.
                        //p_temp comes AFTER p_insert here.
                        p_temp->set_next(p_insert->get_next()); // there is no case where p_insert->get_next() is null  see above
                        p_insert->set_next(p_temp);
                    } else {
                        //p_temp has the smaller trans ID, so will be inserted BEFORE p_insert.
                        // swap the two.
                        // p_temp -> set_next() should be p_insert.
                        // p_insert should be p_temp.
                        Transaction *p_swap = p_insert;
                        p_insert = p_temp;
                        p_temp->set_next(p_swap);
                    }
                } else if ((*p_insert < *p_temp) && (*p_temp < *(p_insert->get_next()))) {
                    // so we are right in between.
//                    std::cout << "insert actually" << std::endl;
                    p_temp->set_next(p_insert->get_next()); //get the handle
                    p_insert->set_next(p_temp); //remap tail
                    break;
                }
                p_insert = p_insert->get_next();
            }
        }
    }
    p_head = p_sorted;
}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History::update_acb_cgl() {
    // update acb, acb_per_share, share_balance, cgl.
    // set to respective transactions in linked list.
    // acb on buy: accumulate amount made for purchases
    // acb on sell: subtract number of shares sold by acb/share from pervious transaction.
    // acb/share on buy: divide acb by share balance
    // acb/share on sell: divide acb (after computes) by share balance.
    // share balance on buy: add share balance from previous transaction with number of shares purchased
    // share balance on sell: previous share balance minus number of shares sold

    // share balance is a running sum of number of shares.
    Transaction *p_temp = p_head;
    double running_acb{};
    unsigned int running_share_balance{};
    double running_acb_per_share{};
    double running_cgl{};
    while (p_temp != nullptr) {
        if (p_temp->get_trans_type()) {
            //true == buy;

            //acb
            running_acb += p_temp->get_amount(); // adds amount paid for shares to running acb.
            p_temp->set_acb(running_acb);

            //share balance
            running_share_balance += p_temp->get_shares(); // adds shares from this transaction to share balance.
            p_temp->set_share_balance(running_share_balance); // sets updated share balance.

            //acb/share
            running_acb_per_share = running_acb / running_share_balance;
            p_temp->set_acb_per_share(running_acb_per_share);
        } else {
            // false == sell;

            //cgl
            running_cgl = p_temp->get_amount() - p_temp->get_shares() * running_acb_per_share;
            p_temp->set_cgl(running_cgl);

            //acb
            running_acb -= p_temp->get_shares() * running_acb_per_share;
            p_temp->set_acb(running_acb);

            //share balance
            running_share_balance -= p_temp->get_shares();
            p_temp->set_share_balance(running_share_balance);

            //acb/share
            running_acb_per_share = running_acb / running_share_balance;
            p_temp->set_acb_per_share(running_acb_per_share);
        }
        p_temp = p_temp->get_next();
    }
}

/*
void History::update_acb_cgl() {
    Transaction * p_iterate = p_head;
    double acb{0};
    int shares_held{0};
    double acb_share{0};
    double cgl_holder{0};
    double acb_holder{0};

    while (p_iterate != nullptr) {
        if (p_iterate->get_trans_type()) {
            acb += p_iterate->get_amount();
            p_iterate->set_acb(acb);
            shares_held += p_iterate->get_shares();
            p_iterate->set_share_balance(shares_held);
            acb_share = acb/shares_held;
            p_iterate->set_acb_per_share(acb_share);
        }
        else {
            acb_holder = acb - (acb_share * p_iterate->get_shares());
            acb = acb_holder;
            p_iterate->set_acb(acb_holder);
            shares_held -= p_iterate->get_shares();
            p_iterate->set_share_balance(shares_held);
            p_iterate->set_acb_per_share(acb_share);
            cgl_holder = p_iterate->get_amount();
            cgl_holder = cgl_holder - (acb_share*p_iterate->get_shares());
            p_iterate->set_cgl(cgl_holder);

        }
        p_iterate = p_iterate->get_next();
    }
}*/

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) {
    // CGL, subtract nuymber of shares sold multiplied by the ACB?Share from the previous transaction (indiv cgl)
    // sum cgl for each year.

    Transaction *p_temp = p_head;
    double running_cgl{};
    while (p_temp != nullptr) {
        if ((p_temp->get_year() == year) && (!p_temp->get_trans_type())) {
            // year is equal and trans type is false (sell);
            running_cgl += p_temp->get_cgl();
        }
        p_temp = p_temp->get_next();
    }

    return running_cgl;

}


// print() Print the transaction history.
//TASK 9
//
void History::print() {
    Transaction *p_temp = p_head;
    std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
    while (p_temp != nullptr) {
        p_temp->print();
        p_temp = p_temp->get_next();
    }
    std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
