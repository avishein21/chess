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
	setBoard.o piece.o queen.o pawn.o king.o piecePage.o fen.o rqbHelper.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o Play play.o board.o termfuncs.o checkPiece.o \
	knight.o setBoard.o piece.o rook.o bish.o queen.o pawn.o king.o piecePage.o fen.o rqbHelper.o

Unit_tests: test_unit.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o Unit_tests test_unit.o 

test_unit.o: test_unit.cpp fen.h
	$(CXX) $(CXXFLAGS) -c test_unit.cpp

play.o: play.cpp piecePage.h board.h setBoard.h
		$(CXX) $(CXXFLAGS) -c play.cpp

fen.o: fen.cpp fen.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c fen.cpp 

setBoard.o: setBoard.cpp setBoard.h pieces/piece.h fen.h
	$(CXX) $(CXXFLAGS) -c setBoard.cpp

piecePage.o: piecePage.cpp piecePage.h termfuncs.h 
		$(CXX) $(CXXFLAGS) -c piecePage.cpp

checkPiece.o: checkPiece.cpp checkPiece.h termfuncs.h 
		$(CXX) $(CXXFLAGS) -c checkPiece.cpp

board.o: board.cpp board.h termfuncs.h checkPiece.h
	$(CXX) $(CXXFLAGS) -c board.cpp

termfuncs.o: termfuncs.cpp termfuncs.h 
	$(CXX) $(CXXFLAGS) -c termfuncs.cpp 

knight.o: pieces/knight.cpp pieces/knight.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c pieces/knight.cpp 

rqbHelper.o: pieces/rqbHelper.cpp pieces/rqbHelper.h pieces/piece.h 
	$(CXX) $(CXXFLAGS) -c pieces/rqbHelper.cpp  

rook.o: pieces/rook.cpp pieces/rook.h pieces/piece.h 
	$(CXX) $(CXXFLAGS) -c pieces/rook.cpp 

bish.o: pieces/bish.cpp pieces/bish.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c pieces/bish.cpp 

queen.o: pieces/queen.cpp pieces/queen.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c pieces/queen.cpp 

pawn.o: pieces/pawn.cpp pieces/pawn.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c pieces/pawn.cpp 

king.o: pieces/king.cpp pieces/king.h pieces/piece.h
	$(CXX) $(CXXFLAGS) -c pieces/king.cpp 

piece.o: pieces/piece.cpp pieces/piece.h 
	$(CXX) $(CXXFLAGS) -c pieces/piece.cpp 




# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm -f $(EXECS)  *.o test_unit