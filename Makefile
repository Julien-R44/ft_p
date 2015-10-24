all:
	make -C serveur/
	make -C client/

fclean:
	make fclean -C serveur/
	make fclean -C client/
