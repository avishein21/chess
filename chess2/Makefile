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


Chess: play.o board.o termfuncs.o checkPiece.o knight.o rook.o bish.o \
	setBoard.o piece.o queen.o pawn.o king.o piecePage.o fen.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o Play play.o board.o termfuncs.o checkPiece.o \
	knight.o setBoard.o piece.o rook.o bish.o queen.o pawn.o king.o piecePage.o fen.o
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

piecePage.o: piecePage.cpp piecePage.h termfuncs.h 
		$(CXX) $(CXXFLAGS) -c piecePage.cpp

checkPiece.o: checkPiece.cpp checkPiece.h knight.h termfuncs.h 
		$(CXX) $(CXXFLAGS) -c checkPiece.cpp

board.o: board.cpp board.h termfuncs.h checkPiece.h piece.h
	$(CXX) $(CXXFLAGS) -c board.cpp

termfuncs.o: termfuncs.cpp termfuncs.h 
	$(CXX) $(CXXFLAGS) -c termfuncs.cpp 

knight.o: knight.cpp knight.h piece.h
	$(CXX) $(CXXFLAGS) -c knight.cpp 

rook.o: rook.cpp rook.h piece.h
	$(CXX) $(CXXFLAGS) -c rook.cpp 

bish.o: bish.cpp bish.h piece.h
	$(CXX) $(CXXFLAGS) -c bish.cpp 

queen.o: queen.cpp queen.h piece.h
	$(CXX) $(CXXFLAGS) -c queen.cpp 

pawn.o: pawn.cpp pawn.h piece.h
	$(CXX) $(CXXFLAGS) -c pawn.cpp 

king.o: king.cpp king.h piece.h
	$(CXX) $(CXXFLAGS) -c king.cpp 

piece.o: piece.cpp piece.h 
	$(CXX) $(CXXFLAGS) -c piece.cpp 


# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm -f $(EXECS)  *.o test_unit