NAME = libft
LIBNAME = $(NAME).a
CFLAGS = -Wall -Werror -Wextra -g

GNLFILES  =	get_next_line
ISFILES   =	ft_isalnum		ft_isalpha			ft_isascii		ft_isdigit	  \
			ft_isprint		ft_isspace			has_elsethan
LISTFILES =	ft_lstadd_back	ft_lstadd_front		ft_lstclear		ft_lstdelone  \
			ft_lstiter		ft_lstlast			ft_lstmap		ft_lstnew	  \
			ft_lstsize
MATHFILES =	ft_abs			ft_atoi				ft_pow			ft_ternary
MEMFILES  =	ft_bzero		ft_calloc			ft_del			ft_memchr	  \
			ft_memcmp		ft_memcpy			ft_memmove		ft_memset	  \
			ft_realloc		has_elsethan
PRINTFILES=	colored_output	display_error		ft_printf		ft_putchar_fd \
			ft_putendl_fd	ft_putnbr_fd		ft_putstr_fd	handle_nbrs	  \
			handle_strs
STRFILES  =	ft_insert_str	ft_itoa				ft_split		ft_strcat	  \
			ft_strchr		ft_strcmp			ft_strdup		ft_striteri	  \
			ft_strjoin		ft_strlcat			ft_strlcpy		ft_strlen	  \
			ft_strmapi		ft_strncmp			ft_strnstr		ft_strrchr	  \
			ft_strstr		ft_strtrim			ft_substr

GNLFILES_FULL = $(addprefix UTILS/GNL/, $(addsuffix .c, $(GNLFILES)))
ISFILES_FULL = $(addprefix UTILS/IS/, $(addsuffix .c, $(ISFILES)))
LISTFILES_FULL = $(addprefix UTILS/LIST/, $(addsuffix .c, $(LISTFILES)))
MATHFILES_FULL = $(addprefix UTILS/MATH/, $(addsuffix .c, $(MATHFILES)))
MEMFILES_FULL = $(addprefix UTILS/MEM/, $(addsuffix .c, $(MEMFILES)))
PRINTFILES_FULL = $(addprefix UTILS/PRINT/, $(addsuffix .c, $(PRINTFILES)))
STRFILES_FULL = $(addprefix UTILS/STR/, $(addsuffix .c, $(STRFILES)))

CFILES = $(GNLFILES_FULL) $(ISFILES_FULL) $(LISTFILES_FULL) $(MATHFILES_FULL) \
		 $(MEMFILES_FULL) $(PRINTFILES_FULL) $(STRFILES_FULL)
OFILES = $(CFILES:.c=.o)


$(LIBNAME) : $(OFILES)
	@rm -f $(LIBNAME)
	@ar -rc $(LIBNAME) $(OFILES)

%.o : %.c compiled
	@cc $(CFLAGS) -I INCLUDES -c $< -o $@

compiled :
	@echo "All $(LIBNAME) files compiled."

all: $(LIBNAME)

clean :
	@rm -f $(OFILES) $(NAME) && echo "$(LIBNAME) object files cleaned.\n"

fclean:
	@rm -f $(OFILES) $(LIBNAME) $(NAME) && echo "$(LIBNAME) cleaned.\n"

re: fclean all

norm:
	@norminette | grep -E --color=always "Error" \
	|| echo "\e[32mnorminette is fine!\e[0m"

allc: $(LIBNAME) clean

rec: fclean allc

rerun: rec
	@cc $(CFLAGS) .main.c -L . -l:$(LIBNAME) -o $(NAME) && ./$(NAME)

rerunvalgrind: rec
	@cc $(CFLAGS) .main.c -L . -l:$(LIBNAME) -o $(NAME) \
	&& valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re : fclean $(LIBNAME)