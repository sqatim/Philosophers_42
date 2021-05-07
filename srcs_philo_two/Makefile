NAME= ../philo_two

SRC_PHILO_TWO_PATH= ../srcs_philo_two

HDR_PHILO_PATH= ../hdrs_philo

OBJ_PHILO_TWO_PATH= obj_philo_two

SRC_PHILO_TWO_NAME=philo_two.c\
					ft_atoi.c\
					tools.c\
					free.c\
					affectation.c\
					print.c\
			
HDR_PHILO_TWO_NAME=philo_two.h 

OBJ_PHILO_TWO_NAME= $(SRC_PHILO_TWO_NAME:.c=.o)

OBJ_PHILO_TWO= $(addprefix $(OBJ_PHILO_TWO_PATH)/,$(OBJ_PHILO_TWO_NAME))
SRC_PHILO_TWO= $(addprefix $(SRC_PHILO_TWO_PATH)/,$(SRC_PHILO_TWO_NAME))
HDR_PHILO_TWO= $(addprefix $(HDR_PHILO_PATH)/,$(HDR_PHILO_TWO_NAME))

FLAGS= -Wall -Wextra -Werror

H_PHILO_FLAG= -I $(HDR_PHILO_PATH)

COMP= gcc

all: $(NAME) 

$(NAME) : $(OBJ_PHILO_TWO)
	@$(COMP) -g $(H_PHILO_FLAG) $(OBJ_PHILO_TWO)  -lpthread -o $@

$(OBJ_PHILO_TWO_PATH)/%.o:  $(SRC_PHILO_TWO_PATH)/%.c $(HDR_PHILO_TWO)
	@mkdir -p $(OBJ_PHILO_TWO_PATH) 
	@$(COMP) -g $(FLAGS) $(H_PHILO_FLAG) -g -o $@ -c $<

clean:
	@rm -rf $(OBJ_PHILO_TWO_PATH)

fclean: clean
	@rm -rf $(NAME)

re : fclean all