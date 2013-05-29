NAME=	toy2ass
MAIN=	toy2assConverter.ml
SRC=	toy2ass.ml
CMX=	toy2ass.cmx

OCAMLOPT= ocamlopt


$(NAME):	cmx
	$(OCAMLOPT) $(CMX) $(MAIN) -o $(NAME)

cmx:
	$(OCAMLOPT) $(SRC)


