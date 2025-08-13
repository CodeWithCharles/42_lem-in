# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:33:26 by cpoulain          #+#    #+#              #
#    Updated: 2025/08/13 14:25:47 by cpoulain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Includes

include			Files.mk
include			Makefile.colors
include			Makefile.msg
include			Makefile.vars

# Objs formatter

OBJS			=	$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(FILES)))

# Phony rules

all: $(TARGET)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) -r $(BIN_DIR)
	$(RM) $(TARGET)
	$(RM) $(THDPTY_LIBFT_H)
	$(RM) $(LIBFT_TARGET)

fclean_all: fclean dellibs

dellibs:
	$(RM) -r $(LIBFT_PATH)

cleanlibs:
	@$(MAKE) clean -C $(LIBFT_PATH)

fcleanlibs:
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

relibs: dellibs libs

libs: $(LIBFT_TARGET)

# Binary / Lib generation

$(TARGET): $(THDPTY_LIBFT_H) $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) $(LIBFT_TARGET) -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

# Third party compilation

$(THDPTY_LIBFT_H): $(LIBFT_TARGET)
	@cp -u $(LIBFT_PATH)/$(LIBFT_INC_H) $@

$(LIBFT_TARGET):
	@if [ ! -d "$(LIBFT_PATH)/.git" ]; then \
		git clone $(LIBFT_GIT) $(LIBFT_PATH);\
	fi
	@$(MAKE) -C $(LIBFT_PATH)
	@cp $(LIBFT_PATH)/$@ ./
	@cp -u $(LIBFT_PATH)/$(LIBFT_INC_H) $(INC_DIR)/

.PHONY: all clean fclean re cleanlibs fcleanlibs fclean_all dellibs libs
