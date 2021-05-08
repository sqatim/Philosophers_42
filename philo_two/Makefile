NAME= philo_two

SRC_PATH= sources

HDR_PATH= header

OBJ_PATH= objects

SRC_NAME=philo_two.c\
		ft_atoi.c\
		tools.c\
		free.c\
		affectation.c\
		print.c\
		tools2.c\
			
HDR_NAME=philo_two.h 

OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ_PHILO_TWO= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC_PHILO_TWO= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR_PHILO_TWO= $(addprefix $(HDR_PATH)/,$(HDR_NAME))

# FLAGS= -Wall -Wextra -Werror

H_PHILO_FLAG= -I $(HDR_PATH)

COMP= gcc

all: $(NAME) 

$(NAME) : $(OBJ_PHILO_TWO)
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_TWO)  -lpthread -o $@
	@echo "										    Made by : \033[1;91mSqatim\033[m"
	@echo "																					  "
	@echo " _____  _    _ _____ _      ____   _____  ____  _____  _    _ ______ _____   _____ " 
	@echo "|  __ \| |  | |_   _| |    / __ \ / ____|/ __ \|  __ \| |  | |  ____|  __ \ / ____|"
	@echo "| |__) | |__| | | | | |   | |  | | (___ | |  | | |__) | |__| | |__  | |__) | (___  "
	@echo "|  ___/|  __  | | | | |   | |  | |\___ \| |  | |  ___/|  __  |  __| |  _  / \___ \ "
	@echo "| |    | |  | |_| |_| |___| |__| |____) | |__| | |    | |  | | |____| | \ \ ____) |"
	@echo "|_|    |_|  |_|_____|______\____/|_____/ \____/|_|    |_|  |_|______|_|  \_|_____/ "
	@echo "																					  "
	@echo "								   Compilation of : $(NAME): \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o:  $(SRC_PATH)/%.c $(HDR_PHILO_TWO)
	@mkdir -p $(OBJ_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -rf $(NAME)

re : fclean all