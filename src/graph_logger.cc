// graph_logger.cc

#include <graph_logger.h>
#include <utils.h>
#include <int.h>

static std::string ConvertEdgeType(GraphLogger::EdgeType edgeType) {
    switch (edgeType) {
        case GraphLogger::EdgeType::Dashed: return "dashed";
        case GraphLogger::EdgeType::Bold:   return "bold";
        case GraphLogger::EdgeType::Dotted: return "dotted";
        case GraphLogger::EdgeType::Solid:  return "solid";
    }
}

GraphLogger* GraphLogger::Logger_ = nullptr;

GraphLogger::GraphLogger(const std::string& logFilename)
    : logFile_(logFilename),
       cnt_(0) {
    if (!logFile_.is_open()) {
        throw std::logic_error("can't open file");
    }
}

GraphLogger::~GraphLogger() {
    logFile_.close();
}

void GraphLogger::createLogger(const std::string& logFilename) {
    delete Logger_;

    Logger_ = new GraphLogger(logFilename);
}

void GraphLogger::deleteLogger() {
    if (Logger_ != nullptr) {
        delete Logger_;
        Logger_ = nullptr;
    }
}

void GraphLogger::log(const std::string& str) {
    if (Logger_ != nullptr) {
        Logger_->logFile_ << str;
    }
}

GraphLogger::Id GraphLogger::addVarNode(const std::string &function, const Int& var, const Color& color) {
    log(StringFormat("%llu [style=\"filled\", color=black, fillcolor=\"#%s\","
                         "shape=record, label=\"function:%s | {name:%s | value:%lli| idx:%llu} | ptr:%p \"];\n",
                         Logger_->cnt_, color.toHex().c_str(), function.c_str(),
                         var.name_.c_str(), var.value_, var.index_, &var));
    return (Logger_->cnt_)++;
}

GraphLogger::Id GraphLogger::addFunctionNode(const std::string &function, const Color& color) {
    log(StringFormat("%llu [style=\"filled\", color=black, fillcolor=\"#%s\","
                         " shape=record, label=\"function:%s\"];\n",
                         Logger_->cnt_, color.toHex().c_str(), function.c_str()));
    return (Logger_->cnt_)++;
}

void GraphLogger::addEdge(Id from, Id to, GraphLogger::EdgeType edgeType, const Color& color) {
    log(StringFormat("%llu -> %llu [style=%s, color=\"#%s\"];\n",
                     from, to, ConvertEdgeType(edgeType).c_str(), color.toHex().c_str()));
}

GraphLogger::Id GraphLogger::getCurrId() {
    return Logger_->cnt_;
}




