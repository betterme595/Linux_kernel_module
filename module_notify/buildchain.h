#ifndef __BUILD_CHAIN_H_
#define __BUILD_CHAIN_H_

extern int register_test_notifier(struct notifier_block *nb);
extern int unregister_test_notifier(struct notifier_block *nb);
extern int test_notifier_call_chain(unsigned long val, void *v);

#endif
