#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
}


int main()
{
	static LIST_HEAD(birthday_list);

	struct birthday *person;
	
}