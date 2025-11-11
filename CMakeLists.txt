cmake_minimum_required(VERSION 4.0)
project(warzone-game)

set(CMAKE_CXX_STANDARD 26)

add_executable(warzone-game MainDriver.cpp
        Cards.h
        Cards.cpp
        CardsDriver.cpp
        CardsDriver.h
        GameEngine.cpp
        GameEngine.h
        GameEngineDriver.cpp
        GameEngineDriver.h
        Map.cpp
        Map.h
        MapDriver.cpp
        MapDriver.h
        Orders.cpp
        Orders.h
        OrdersDriver.cpp
        OrdersDriver.h
        Player.cpp
        Player.h
        PlayerDriver.cpp
        PlayerDriver.h)