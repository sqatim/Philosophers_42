NAME= ../philo_one

SRC_PHILO_ONE_PATH= ../srcs_philo_one

HDR_PHILO_PATH= ../hdrs_philo


OBJ_PHILO_ONE_PATH= obj_philo_one

SRC_PHILO_ONE_NAME=philo_one.c\
					tools.c\
					ft_atoi.c\
					free.c\
					affectation.c\
					print.c\

HDR_PHILO_ONE_NAME=philo_one.h 

OBJ_PHILO_ONE_NAME= $(SRC_PHILO_ONE_NAME:.c=.o)

OBJ_PHILO_ONE= $(addprefix $(OBJ_PHILO_ONE_PATH)/,$(OBJ_PHILO_ONE_NAME))
SRC_PHILO_ONE= $(addprefix $(SRC_PHILO_ONE_PATH)/,$(SRC_PHILO_ONE_NAME))
HDR_PHILO_ONE= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_ONE_NAME))

FLAGS= -Wall -Wextra -Werror

H_PHILO_FLAG= -I $(HDR_PHILO_PATH)

COMP= gcc

all: $(NAME) 

$(NAME) : $(OBJ_PHILO_ONE)
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_ONE) -lpthread -o $@

$(OBJ_PHILO_ONE_PATH)/%.o:  $(SRC_PHILO_ONE_PATH)/%.c $(HDR_PHILO_ONE)
	@mkdir -p $(OBJ_PHILO_ONE_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PHILO_ONE_PATH)

fclean: clean
	@rm -rf $(NAME)

re : fclean all