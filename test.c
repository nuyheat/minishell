
#include "minishell.h"

t_token_info	*makenode()
{
	t_token_info	newtoken;
	t_token_info	*ptr;
	newtoken.token = "abc";
	newtoken.flags = 1;
	ptr = &newtoken;
	return (ptr);
}
void	addlist(t_token_list list)
{
	t_token_list newlist;
	newlist.next = NULL;
	newlist.token = makenode();

	list.next = &newlist;
}

int main()
{
	t_token_list list;
	char	*str;

	str = NULL;
	addlist(list);
	printf("str : %s\n flg : %d\n", list.next->token, list.next->token->flags);
}
