NAME= philo_one

SRC_PHILO_ONE_PATH= srcs_philo_one
SRC_PHILO_TWO_PATH= srcs_philo_two
SRC_PHILO_THREE_PATH= srcs_philo_three


HDR_PHILO_PATH= hdrs_philo


OBJ_PHILO_ONE_PATH= obj_philo_one
OBJ_PHILO_TWO_PATH= obj_philo_two
OBJ_PHILO_THREE_PATH= obj_philo_three


SRC_PHILO_ONE_NAME=philo_one.c\
					tools.c\
					ft_atoi.c\

SRC_PHILO_TWO_NAME=philo_two.c\
			
SRC_PHILO_THREE_NAME=philo_three.c\


HDR_PHILO_ONE_NAME=philo_one.h 
HDR_PHILO_TWO_NAME=philo_two.h 
HDR_PHILO_THREE_NAME=philo_three.h 

OBJ_PHILO_ONE_NAME= $(SRC_PHILO_ONE_NAME:.c=.o)
OBJ_PHILO_TWO_NAME= $(SRC_PHILO_TWO_NAME:.c=.o)
OBJ_PHILO_THREE_NAME= $(SRC_PHILO_THREE_NAME:.c=.o)


OBJ_PHILO_ONE= $(addprefix $(OBJ_PHILO_ONE_PATH)/,$(OBJ_PHILO_ONE_NAME))
SRC_PHILO_ONE= $(addprefix $(SRC_PHILO_ONE_PATH)/,$(SRC_PHILO_ONE_NAME))
HDR_PHILO_ONE= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_ONE_NAME))

OBJ_PHILO_TWO= $(addprefix $(OBJ_PHILO_TWO_PATH)/,$(OBJ_PHILO_TWO_NAME))
SRC_PHILO_TWO= $(addprefix $(SRC_PHILO_TWO_PATH)/,$(SRC_PHILO_TWO_NAME))
HDR_PHILO_TWO= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_TWO_NAME))

OBJ_PHILO_THREE= $(addprefix $(OBJ_PHILO_THREE_PATH)/,$(OBJ_PHILO_THREE_NAME))
SRC_PHILO_THREE= $(addprefix $(SRC_PHILO_THREE_PATH)/,$(SRC_PHILO_THREE_NAME))
HDR_PHILO_THREE= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_THREE_NAME))


# FLAGS= -Wall -Wextra -Werror


H_PHILO_FLAG= -I $(HDR_PHILO_PATH)


COMP= gcc

all: $(NAME) 

$(NAME) : $(OBJ_PHILO_ONE) $(OBJ_PHILO_TWO) $(OBJ_PHILO_THREE)
	@rm -rf $(NAME)
	@rm -rf philo_two
	@rm -rf philo_three
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_ONE) -lpthread -o $@
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_TWO)  -lpthread -o philo_two
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_THREE)  -lpthread -o philo_three
	@echo "										    Made by : \033[1;91mSqatim\033[m"
	@echo "																					  "
	@echo " _____  _    _ _____ _      ____   _____  ____  _____  _    _ ______ _____   _____ " 
	@echo "|  __ \| |  | |_   _| |    / __ \ / ____|/ __ \|  __ \| |  | |  ____|  __ \ / ____|"
	@echo "| |__) | |__| | | | | |   | |  | | (___ | |  | | |__) | |__| | |__  | |__) | (___  "
	@echo "|  ___/|  __  | | | | |   | |  | |\___ \| |  | |  ___/|  __  |  __| |  _  / \___ \ "
	@echo "| |    | |  | |_| |_| |___| |__| |____) | |__| | |    | |  | | |____| | \ \ ____) |"
	@echo "|_|    |_|  |_|_____|______\____/|_____/ \____/|_|    |_|  |_|______|_|  \_|_____/ "
	@echo "																					  "
	@echo "								   Compilation of : philosophers: \033[1;32mOK\033[m"


$(OBJ_PHILO_ONE_PATH)/%.o:  $(SRC_PHILO_ONE_PATH)/%.c $(HDR_PHILO_ONE)
	@mkdir -p $(OBJ_PHILO_ONE_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

$(OBJ_PHILO_TWO_PATH)/%.o:  $(SRC_PHILO_TWO_PATH)/%.c $(HDR_PHILO_TWO)
	@mkdir -p $(OBJ_PHILO_TWO_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

$(OBJ_PHILO_THREE_PATH)/%.o:  $(SRC_PHILO_THREE_PATH)/%.c $(HDR_PHILO_THREE)
	@mkdir -p $(OBJ_PHILO_THREE_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PHILO_ONE_PATH)
	@rm -rf $(OBJ_PHILO_TWO_PATH)
	@rm -rf $(OBJ_PHILO_THREE_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@rm -rf philo_one
	@rm -rf philo_two
	@rm -rf philo_three
	@echo "\033[0;31m>> all obbjects are deleted.\033[0m" 

re : fclean all