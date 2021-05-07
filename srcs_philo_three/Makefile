NAME= ../philo_three

SRC_PHILO_THREE_PATH= ../srcs_philo_three


HDR_PHILO_PATH= ../hdrs_philo

OBJ_PHILO_THREE_PATH= obj_philo_three

SRC_PHILO_THREE_NAME=philo_three.c\
					ft_atoi.c\
					tools.c\
					free.c\
					affectation.c\
					print.c\

HDR_PHILO_THREE_NAME=philo_three.h 

OBJ_PHILO_THREE_NAME= $(SRC_PHILO_THREE_NAME:.c=.o)

OBJ_PHILO_THREE= $(addprefix $(OBJ_PHILO_THREE_PATH)/,$(OBJ_PHILO_THREE_NAME))
SRC_PHILO_THREE= $(addprefix $(SRC_PHILO_THREE_PATH)/,$(SRC_PHILO_THREE_NAME))
HDR_PHILO_THREE= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_THREE_NAME))

FLAGS= -Wall -Wextra -Werror

H_PHILO_FLAG= -I $(HDR_PHILO_PATH)


COMP= gcc

all: $(NAME) 

$(NAME) : $(OBJ_PHILO_THREE)
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_THREE)  -lpthread -o $@

$(OBJ_PHILO_THREE_PATH)/%.o:  $(SRC_PHILO_THREE_PATH)/%.c $(HDR_PHILO_THREE)
	@mkdir -p $(OBJ_PHILO_THREE_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PHILO_THREE_PATH)

fclean: clean
	@rm -rf $(NAME)

re : fclean all