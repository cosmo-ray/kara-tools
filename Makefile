NAME=	toy2ass
SRC=	toy2ass.ml\
	toy2assConverter.ml
CMX=	$(SRC:.ml=.cmx)
OBJ=	$(SRC:.ml=.o)

OCAMLOPT= ocamlopt

all:	$(NAME)

$(NAME):	cmx
	$(OCAMLOPT) $(CMX) -o $(NAME)

generateur:
	$(OCAMLOPT) generatoy.ml -o generatoy


cmx:
	$(OCAMLOPT) $(SRC)


clean:
	rm -rvf $(CMX) $(OBJ)

fclean: clean
	rm -rvf $(NAME)

re:	clean all
