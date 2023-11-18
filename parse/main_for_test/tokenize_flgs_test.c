#include "minishell.h"

int main()
{
	int	    new_flgs;
    t_list  *list;
    t_list  *list_head;

    list_head = list_init(&list);
	new_flgs = 0;
	flgs_quote(&new_flgs, '\"');
	flgs_redirect(&new_flgs, '>');
	flgs_redirect(&new_flgs, '<');
	flgs_redirect(&new_flgs, '>');
	flgs_redirect(&new_flgs, '>');
	flgs_redirect(&new_flgs, '<');
	printf("COMMAND           : %d\n", new_flgs & COMMAND);
	printf("DQUOTE            : %d\n", new_flgs & DQUOTE);
	printf("DQUOTE_END        : %d\n", new_flgs & DQUOTE_END);
	printf("QUOTE             : %d\n", new_flgs & QUOTE);
	printf("QUOTE_END         : %d\n", new_flgs & QUOTE_END);
	printf("REDIRECT_LEFT     : %d\n", new_flgs & REDIRECT_LEFT);
	printf("REDIRECT_LEFT_END : %d\n", new_flgs & REDIRECT_LEFT_END);
	printf("REDIRECT_RIGHT    : %d\n", new_flgs & REDIRECT_RIGHT);
	printf("REDIRECT_RIGHT_END: %d\n", new_flgs & REDIRECT_RIGHT_END);
	printf("PIPE              : %d\n", new_flgs & PIPE);
	printf("DOLLAR            : %d\n", new_flgs & DOLLAR);
	printf("DOLLAR_PARAM      : %d\n", new_flgs & DOLLAR_PARAM);
} // flgs 함수 테스트용 main 함수