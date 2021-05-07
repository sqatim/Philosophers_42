NAME= philo_one\
		philo_two\
		philo_three\


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
					free.c\
					affectation.c\
					print.c\

SRC_PHILO_TWO_NAME=philo_two.c\
					ft_atoi.c\
					tools.c\
					free.c\
					affectation.c\
					print.c\
			
SRC_PHILO_THREE_NAME=philo_three.c\
					ft_atoi.c\
					tools.c\
					free.c\
					affectation.c\
					print.c\


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

all: $(NAME) one two three

$(NAME) : 
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

one: 
	@make -sC $(SRC_PHILO_ONE_PATH)

two: 
	@make -sC $(SRC_PHILO_TWO_PATH)

three: 
	@make -sC $(SRC_PHILO_THREE_PATH)

clean:
	@make clean -C $(SRC_PHILO_ONE_PATH)
	@make clean -C $(SRC_PHILO_TWO_PATH)
	@make clean -C $(SRC_PHILO_THREE_PATH)
	@echo "\033[1;33m>> all objects files are deleted.\033[0m" 

fclean: clean
	@make fclean -C $(SRC_PHILO_ONE_PATH)
	@make fclean -C $(SRC_PHILO_TWO_PATH)
	@make fclean -C $(SRC_PHILO_THREE_PATH)
	@echo "\033[0;31m>> all obbjects are deleted.\033[0m" 

re : fclean all