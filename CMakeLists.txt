cmake_minimum_required(VERSION 3.17)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 main.cpp ColonAutomaton.cpp ColonDashAutomaton.cpp Lexer.cpp Token.cpp MatcherAutomaton.h MatcherAutomaton.cpp IDAutomaton.h CommentAutomaton.h StringAutomaton.h StringAutomaton.cpp IDAutomaton.cpp CommentAutomaton.cpp)