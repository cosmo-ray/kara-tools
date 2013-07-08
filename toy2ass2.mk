NAME=	toy2ass2
SRC=	toy2ass.ml\
	toy2assConverter2.ml

CMX=	$(SRC:.ml=.cmx)
OBJ=	$(SRC:.ml=.o)

OCAMLOPT= ocamlopt

all:	$(NAME)

$(NAME):	cmx
	$(OCAMLOPT) $(CMX) -o $(NAME)

cmx:
	$(OCAMLOPT) $(SRC)


clean:
	rm -rvf $(CMX) $(OBJ)

fclean: clean
	rm -rvf $(NAME)

re:	clean all
