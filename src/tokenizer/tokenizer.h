/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dukim <dukim@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:58 by dukim             #+#    #+#             */
/*   Updated: 2024/12/17 23:21:59 by dukim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../../inc/minishell.h"

# define WORD_LEN 64

typedef enum e_token_type
{
	WORD,
	SYMBOL,
}	t_token_type;

typedef struct s_word
{
	char	*content;
	size_t	idx;
	size_t	max_len;
}	t_word;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
}	t_token;

void	dollar_parser(t_word *word, char *pre, size_t *i, t_list *env_list);
void	quote_parser(char **line, t_word *word);
t_bool	is_specital_tokench(char ch);
void	append_token_inlist(t_list **tokenlst, t_word *word, \
							t_token_type type, t_list *env_list);

// word utils
void	init_word(t_word *word);
void	append_ch_inword(t_word *word, char ch);
void	append_str_inword(t_word *word, char *str);
void	convert_wordcotent(t_word *word, t_list *env_list);

// heredoc
void	handle_heredoc(t_list **tokenlst, char **line, \
						t_word *word, t_list *envlst);

#endif