#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched/signal.h>
#include <linux/oom.h>
#include <linux/version.h>

/*Iterate over all the elements in get_num_physpages and print mem usage stats*/
/*Page frame numbers start at 0 and continue until get_num_physpage(). However there*/
/*can be holes in memory so need to check each pfn to make sure it is pfn_valid().*/
/*Once we've pfn_to_page() we can get a page's folio with page_folio().*/

static int __init my_init(void)
{
	pr_info("Module loaded\n");
	unsigned long num_physpages = get_num_physpages();
	unsigned long pfn, valid = 0;
	struct page *my_page;
	struct folio *my_folio;
	int free, locked = 0;  // other stats but will just show these for now
	pr_info("Number of pages: %ld\n", num_physpages);
	for (pfn = 0; pfn < num_physpages; pfn++) {
		if (pfn_valid(pfn)){
			valid++;
			my_page = pfn_to_page(pfn);
			/*A page with page_count of 0 is a free page*/
			if (page_count(my_page) == 0) {
				free++;
			}
			my_folio = page_folio(my_page);
			if (folio_test_locked(my_folio)) {
				locked++;
			}
		}
	}
	pr_info("Num valid PFNs: %ld\n", valid);
	pr_info("Num free pages: %d\n", free);
	pr_info("Num locked: %d\n", locked);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ALEX");
MODULE_LICENSE("GPL v2");
