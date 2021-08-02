TARGET = so_long
CC = gcc
CF = -Wall -Wextra -Werror -Imlx -Iincludes -g
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit
SRCS =	main.c \
		draw.c \
		draw2.c \
		bmp_reader.c \
		get_next_line.c \
		get_next_line_utils.c \
		ber_reader.c \
		util.c \
		util2.c
OBJS = $(SRCS:.c=.o)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CF) $(MLX) $^ -o $@

f : all
	./so_long maps/map_basic2.ber

f2 : all
	./so_long maps/map_100.ber

%.o : %.c
	$(CC) $(CF) $< -c

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(TARGET)

re : fclean all

t1 : all
	echo 'case1: invalid char in map'
	./so_long maps/map_invalidchar.ber
	echo 'case2: no player in map'
	./so_long maps/map_noplayer.ber
	echo 'case3: not rect map in map'
	./so_long maps/map_notrect.ber
	echo 'case4: map is not surrounded by wall'
	./so_long maps/map_notsurround.ber

.PHONY : all clean fclean re
