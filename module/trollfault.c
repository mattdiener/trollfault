#include <linux/module.h>
#include <linux/kprobes.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/signal.h>
#include <linux/mm.h>
#include <linux/fs.h>
#include <linux/kmod.h>

static struct jprobe jp;

static int send_signal_probe_call(int sig, struct siginfo *info, struct task_struct *t, int group){
	if (sig == SIGSEGV) {
		/*
		 * Everything to do with running the mpg123 executable here
		 * Run a different application by changing the values in argv
		 */
		char* argv[] = {"/usr/bin/mpg123","/etc/troll/airhorn.mp3",NULL};
		char* envp[] = {"HOME=/","TERM=linux","PATH=/sbin:/usr/sbin:/bin:/usr/bin"};
		call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
	}

	jprobe_return();
	return 0;
}

/*
 * The jprobe structure: "entry" is a function pointer to a function that has the same 
 *                        signature as the function that is being probed
 */
static struct jprobe jp = {
	.entry = (kprobe_opcode_t *)send_signal_probe_call
};

static int __init troll_fault_init(void){
	jp.kp.addr = (kprobe_opcode_t *)kallsyms_lookup_name("send_signal");
	register_jprobe(&jp);
	return 0;
}

static void __exit troll_fault_exit(void){
	unregister_jprobe(&jp);
}

module_init(troll_fault_init);
module_exit(troll_fault_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Matt Diener");
MODULE_DESCRIPTION("Detects segfaults and runs executables");
