#########################################################
#             HOMEWORK 2: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow -O2 -std=c++11

# ***TODO***
# Metrosim rule - you need to fill in the linking command, as well as 
# target rules for Passenger.o, MetroSim.o, and main.o.
# Please use the rules provided below for PassengerQueue.o as an example for
# what to do.
# If you add other classes, you'll have to add their .o files here.
# Don't forget:  the clang++ command must be indented with a TAB character
# and be all on one line.


Chess: play.o board.o termfuncs.o checkPiece.o knight.o rook.o bish.o\
	queen.o king.o pawn.o piecePage.o chessbot.o setBoard.o fen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o Play play.o board.o termfuncs.o \
	checkPiece.o knight.o rook.o bish.o queen.o king.o pawn.o piecePage.o chessbot.o setBoard.o fen.o

Unit_tests: test_unit.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o Unit_tests test_unit.o 

test_unit.o: test_unit.cpp fen.h
	$(CXX) $(CXXFLAGS) -c test_unit.cpp

play.o: play.cpp piecePage.h board.h setBoard.h
		$(CXX) $(CXXFLAGS) -c play.cpp

fen.o: fen.cpp fen.h piece.h
	$(CXX) $(CXXFLAGS) -c fen.cpp 

setBoard.o: setBoard.cpp setBoard.h piece.h fen.h
	$(CXX) $(CXXFLAGS) -c setBoard.cpp

board.o: board.cpp board.h termfuncs.h checkPiece.h king.h piece.h chessbot.h fen.h
	$(CXX) $(CXXFLAGS) -c board.cpp

termfuncs.o: termfuncs.cpp termfuncs.h 
	$(CXX) $(CXXFLAGS) -c termfuncs.cpp 

knight.o: knight.cpp knight.h piece.h
	$(CXX) $(CXXFLAGS) -c knight.cpp 

rook.o: rook.cpp rook.h piece.h
	$(CXX) $(CXXFLAGS) -c rook.cpp 

bish.o: bish.cpp bish.h piece.h
	$(CXX) $(CXXFLAGS) -c bish.cpp 

queen.o: queen.cpp queen.h bish.h rook.h piece.h
	$(CXX) $(CXXFLAGS) -c queen.cpp 

king.o: king.cpp king.h piece.h checkPiece.h
	$(CXX) $(CXXFLAGS) -c king.cpp 

pawn.o: pawn.cpp pawn.h piece.h
	$(CXX) $(CXXFLAGS) -c pawn.cpp 

chessbot.o: chessbot.cpp chessbot.h checkPiece.h
	$(CXX) $(CXXFLAGS) -c chessbot.cpp 


# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm -f $(EXECS)  *.o test_unit