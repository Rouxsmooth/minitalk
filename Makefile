NAME = minitalk
LIBNAME = $(NAME).a
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

CFILES=	SRCS/globals.c			SRCS/client_utils.c	SRCS/sending.c	\
		SRCS/sending_utils.c	SRCS/server_utils.c	SRCS/clientflags.c
OFILES = $(CFILES:.c=.o)
INCLUDE_LIBFT = -L $(LIBFT_DIR) -l:$(LIBFT)
CFLAGS = -Wall -Werror -Wextra -g

$(LIBNAME): $(LIBFT) $(OFILES)
	@cp $(LIBFT) $(LIBNAME)
	@echo "All $(NAME) files compiled.\n"
	@ar -rc $(LIBNAME) $(OFILES) $(LIBFT) 
	@cc $(CFLAGS) SRCS/server.c -L . -l:minitalk.a $(INCLUDE_LIBFT) -o server 
	@cc $(CFLAGS) SRCS/client.c -L . -l:minitalk.a $(INCLUDE_LIBFT) -o client 

%.o: %.c 
	@cc $(CFLAGS)  -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

bonus: $(LIBFT) $(OBONUSFILES)
	@echo "Bonus files compiled.\n"
	@cp $(LIBFT) $(NAME)
	@ar -rc $(NAME) $(OBONUSFILES) $(LIBFT)

allc: $(LIBNAME) clean

all: $(LIBNAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OFILES) a.out && echo "$(NAME) object files cleaned."

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(OFILES) $(LIBNAME) server client && echo "$(NAME) cleaned.\n"

re: fclean $(LIBNAME)

norm:
	@norminette | grep -E --color=always "Error" || echo "\e[32mnorminette is fine!\e[0m"

allc: $(LIBNAME) clean

rec: fclean allc

.PHONY:
	all