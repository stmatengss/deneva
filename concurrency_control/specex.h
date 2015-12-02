#ifndef _SPECEX_H_
#define _SPECEX_H_

#include "row.h"


// TODO For simplicity, the txn hisotry for SPECEX is oganized as follows:
// 1. history is never deleted.
// 2. hisotry forms a single directional list. 
//		history head -> hist_1 -> hist_2 -> hist_3 -> ... -> hist_n
//    The head is always the latest and the tail the youngest. 
// 	  When history is traversed, always go from head -> tail order.

class txn_man;
class set_ent;

class SpecEx {
public:
	void init();
  void clear(); 
	RC validate(txn_man * txn);
	volatile bool lock_all;
	uint64_t lock_txn_id;
private:

	bool test_valid(set_ent * set1, set_ent * set2);
	RC get_rw_set(txn_man * txni, set_ent * &rset, set_ent *& wset);
	
	// "history" stores write set of transactions with tn >= smallest running tn
	set_ent * history;
	set_ent * active;
	uint64_t his_len;
	uint64_t active_len;
	volatile uint64_t tnc; // transaction number counter
	pthread_mutex_t latch;
};

#endif
