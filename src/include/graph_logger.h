#pragma once

#include <vector>
#include <string>
#include <fstream>

#include <color.h>

struct Int;

struct GraphLogger {    
    enum class EdgeType {
        Dashed,
        Bold,
        Dotted,
        Solid
    };

    using Id = uint64_t;

    static void createLogger(const std::string& logFilename);
    static void deleteLogger();

    static void log(const std::string& str);

    static Id addVarNode(const std::string &function, const Int& var, const Color& color = Colors::LIGHT_BLUE);

    static Id addFunctionNode(const std::string &function, const Color& color = Colors::LIGHT_BLUE);

    static void addEdge(Id from, Id to, EdgeType edgeType = EdgeType::Bold, const Color& color = Colors::BLACK);

    static Id getCurrId();

    GraphLogger(const GraphLogger& other) = delete;
    GraphLogger& operator=(const GraphLogger& other) = delete;
    GraphLogger(GraphLogger&& other) = delete;
    GraphLogger& operator=(GraphLogger&& other) = delete;

private:
    explicit GraphLogger(const std::string& logFilename);
    ~GraphLogger();

    static Color ConstructColor;
    static Color FunctionColor;

    Id  cnt_;
    std::ofstream logFile_;
    static GraphLogger* Logger_;
};