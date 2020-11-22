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
    trans_type = buy_sell_trans; //this is wrong trans_type isa sting
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
    delete p_next;
    p_next = nullptr;

}


// Overloaded < operator.
// TASK 2
//

bool Transaction::operator<(Transaction const &other) { ///this is very important please fix this.
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
    } else if (this-> year == other.year) {
        //same year so check month
        if(this->month < other.month) {
            // the left one is a lesser month, so we're automatically good
            return true;
        } else if (this->month == other.month) {
            //same month so check day
            if (this->day < other.day) {
                // left day is less!
                return true;
            } else if (this->trans_id < other.trans_id){
                return true; // is there a case where same day is approved ? -> yes there is
                //smaller trans id wins.
            }
        }
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

}


// Destructor
// TASK 3
//

History::~History() {
    while(p_head != nullptr) {
        Transaction *p_temp{p_head};

        p_head = p_head->get_next();
        delete p_temp;
        p_temp = nullptr;
    }
}


// read_transaction(...): Read the transaction history from file.
// TASK 4
//
void History::read_history() {

}


// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans) {

}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {

}


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl() {

}


// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) {

}


// print() Print the transaction history.
//TASK 9
//
void History::print() {

}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }


#endif
