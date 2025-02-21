#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration{
public:
Configuration();
void init();
char* getDeviceName();
char* getSerialNumber(); 
void setDeviceName (char *);
void setSerialNumber (char *);


private:
 

  

};
#endif //CONFIGURATION_H