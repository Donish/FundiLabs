#include "logger.h"
#include "logger_builder_concrete.h"
#include "json_builder_concrete.h"

int main()
{
    logger_builder* builder = new logger_builder_concrete();
    json_builder* builder2 = new json_builder_concrete();
    
    // через builder
    logger *constructed_logger = builder
        ->add_stream("file1.txt", logger::severity::information)
        ->add_stream("file2.txt", logger::severity::warning)
        ->construct();

    // через json
    logger *constructed_logger_2 = builder2
        ->add_stream("json_logger.json")
        ->construct();

    constructed_logger
        ->log("must be in file 1", logger::severity::information);
    constructed_logger
        ->log("must be in file 1 and 2", logger::severity::critical);

    constructed_logger_2
        ->log("must be in file 2 and 3", logger::severity::error);
    constructed_logger_2
        ->log("must be in file 3", logger::severity::trace);

    delete constructed_logger_2;
    delete constructed_logger;
    delete builder;
    delete builder2;

    return 0;
}