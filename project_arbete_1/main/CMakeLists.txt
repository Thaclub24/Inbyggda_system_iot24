idf_component_register(SRCS "main.cpp" 
                    INCLUDE_DIRS "../components/Ljussensor/include"
                       REQUIRES Ljussensor
                    REQUIRES driver)