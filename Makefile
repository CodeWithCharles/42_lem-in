# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpoulain <cpoulain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 16:33:26 by cpoulain          #+#    #+#              #
#    Updated: 2025/08/18 12:09:18 by cpoulain         ###   ########.fr        #
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
	$(RM) $(THDPTY_LIBFT_H)
	$(RM) $(LIBFT_TARGET)

cleanlibs:
	@$(MAKE) clean -C $(LIBFT_PATH)

fcleanlibs:
	@$(MAKE) fclean -C $(LIBFT_PATH)

re: fclean all

relibs: dellibs libs

libs: $(LIBFT_TARGET)

# Binary / Lib generation

$(TARGET): $(THDPTY_LIBFT_H) $(OBJS) $(VIS_NODE)
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


$(VIS_NODE):
	@if [ ! -d "$(VIS_TARGET)" ]; then \
		git clone $(VIS_GIT) $(VIS_DIR);\
	fi
	@if [ ! -d "$(VIS_NODE)" ]; then \
		cd $(VIS_DIR) && npm i;\
	fi

vis_to_dev:
	cd $(VIS_DIR) && $(GIT_REMOTE_RM) && $(GIT_REMOTE_ADD) $(VIS_GIT_SSH)

vis_to_prod:
	cd $(VIS_DIR) && $(GIT_REMOTE_RM) && $(GIT_REMOTE_ADD) $(VIS_GIT)

.PHONY: all clean fclean re cleanlibs fcleanlibs fclean_all dellibs libs vis_to_dev vis_to_prod
