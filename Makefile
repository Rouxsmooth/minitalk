NAME = minitalk
LIBNAME = $(NAME).a
LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

CFILES = SRCS/server.c 
BONUSFILES = server_bonus.c bonus.c
OFILES = $(CFILES:.c=.o)
OBONUSFILES = $(BONUSFILES:.c=.o)

CFLAGS = -Wall -Werror -Wextra -L $(LIBFT_DIR) -l:$(LIBFT)

$(LIBNAME): $(LIBFT) $(OFILES)
	@cp $(LIBFT) $(LIBNAME)
	@echo "All $(NAME) files compiled.\n"
	@ar -rc $(LIBNAME) $(OFILES) $(LIBFT)

%.o: %.c 
	@cc $(CFLAGS) -c $< -o $@

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
	@rm -f $(OFILES) $(NAME) a.out && echo "$(NAME) cleaned.\n"

re : fclean $(LIBNAME)

norm:
	@norminette | grep -E --color=always "Error" || echo "\e[32mnorminette is fine!\e[0m"

allc: $(LIBNAME) clean

rec: fclean allc