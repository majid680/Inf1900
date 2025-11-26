#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "robot.h"
#include "rs232.h"
#include "sound.h"
#include "motor.h"
#include "sensors.h"
#include "timer.h"
#include "symbol.h"
#include "delay.h"
#include "led.h"
#include "button.h"
#include "report.h"

uint8_t Robot::lastError = 0;
bool Robot::leftCorrection = false;
DetectedSymbol Robot::detectedSymbols[3];
uint8_t Robot::symbolVisitedCounter = 0;
bool Robot::symbolBehavior = false;
bool Robot::redTape = false;

BetweenSymbols Robot::betweenSymbols[3];

Led Robot::led = Led(&PORTB, PB0, PB1);
Button Robot::button = Button(&PIND, PD2);


void Robot::initializationOfMaterials()
{
    SerialCommunication::initializationUART();
    Sound::initializeSound();
    Motor::setMotor();
    DistanceSensor::setCaptor();
    MakerLine::setCaptor();
}

bool Robot::findLine() // DONT FORGET THE ISR THAT INC THE TIMER1 COUNTER
{
    Motor::stop();
    for(uint8_t rotation = 0; rotation < 4; rotation++){
        Timer1::startCounter(10); 
        while (Timer1::getTimerCounter() < 120 && MakerLine::getAnalogInput() <= 26)
        {  
            if (rotation == 0 || rotation == 3)
                Motor::turnRight(MAX_SPEED);
            else    
                Motor::turnLeft(MAX_SPEED);
        }
        Motor::stop();
        _delay_ms(750);
        if (MakerLine::getAnalogInput() > 26){
            return true; //Detected a line
        }
    }
    return false; // No line detected
}


void Robot::correct(uint8_t absoluteValueError)
{
    uint8_t leftSpeed, rightSpeed;

    uint16_t adjustment = (KP * absoluteValueError + KD * (absoluteValueError - lastError)) / 100;
    if (adjustment > MAX_SPEED)
        adjustment = MAX_SPEED;
    lastError = absoluteValueError;

    
    if (leftCorrection == false)
    {
        leftSpeed = MAX_SPEED;
        rightSpeed = MAX_SPEED - adjustment;
    }
    else
    {
        leftSpeed = MAX_SPEED - adjustment;
        rightSpeed = MAX_SPEED;
    }
    Motor::turnForward(leftSpeed, rightSpeed);
}



uint8_t Robot::computeError(uint8_t position)
{
    uint8_t absoluteValueError = 0;
    if (GOAL < position) 
    {
        absoluteValueError = position - GOAL;
        leftCorrection = false; 
    }
    else
    {
        absoluteValueError = GOAL - position;
        leftCorrection = true; 
    }
    return absoluteValueError;
}



void Robot::followLine()  
{
    uint8_t position = MakerLine::getAnalogInput(); // entre 26 et 230

    uint8_t absoluteValueError = computeError(position);

    correct(absoluteValueError);


   
    if(MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput2() && !MakerLine::getDigitalInput3() && !MakerLine::getDigitalInput4() && !MakerLine::getDigitalInput5()){
        Motor::turnForward(MAX_SPEED - 10, MAX_SPEED, true);
        _delay_ms(300);
    }
    else if (!MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput2() && !MakerLine::getDigitalInput3() && !MakerLine::getDigitalInput4() && MakerLine::getDigitalInput5()){
        Motor::turnForward(MAX_SPEED, MAX_SPEED - 10, true);
        _delay_ms(300);
    }
    

    Robot::led.amber();
}




void Robot::switchDetected()
{
    goToLine(800);
    detectedSymbols[symbolVisitedCounter] = DetectedSymbol::SWITCH;
    symbolVisitedCounter++;
    symbolBehavior = true;
}

void Robot::goToLine(uint16_t time, bool scan)  //scan in true by default
{
    Motor::bothWheels(MAX_SPEED, Direction::forward, true);
    Delay::dynamicDelay(time);      
    if(MakerLine::allWhiteDetected() && scan){
        findLine();

    }

}

DetectedSymbol Robot::getLastVisitedSymbol(){
    if(symbolVisitedCounter > 0)
        return detectedSymbols[symbolVisitedCounter - 1];
    return DetectedSymbol::ERROR;
}



void Robot::symbolDetection(){

    if(MakerLine::allWhiteDetected()){    // switch symbol
        switchDetected();
    }

    else if(MakerLine::allBlackDetected()){
        Symbol::findMatchingBlackSymbol();  

        

        if(getLastVisitedSymbol() == DetectedSymbol::MOTOR){   //Motor symbol

            Motor::bothWheels(MAX_SPEED, Direction::forward, true);
            _delay_ms(500);

            while(MakerLine::allWhiteDetected())
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);

            if (MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput5()){
                _delay_ms(15);
                if(MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED - 10, MAX_SPEED);
                    _delay_ms(1000);
                }
                else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1000);
                }
            }
            else if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5()){
                _delay_ms(15);
                if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED, MAX_SPEED - 10);
                    _delay_ms(1000);
                }
                else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1000);
                }
            }
            else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1000);
            }

            goToLine(200, false);                         
            
        }
        else if(getLastVisitedSymbol() == DetectedSymbol::PIEZO){      //Piezo symbol  
            
            _delay_ms(5);
            if (MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput5()){
                _delay_ms(40);
                if(MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED, MAX_SPEED - 10);
                    _delay_ms(1200);
                }
                else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1200);
                }
            }
            else if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5()){
                _delay_ms(40);
                if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED - 10, MAX_SPEED);
                    _delay_ms(1200);
                }
                else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1200);
                }
            }
            else{
                Motor::bothWheels(MAX_SPEED, Direction::forward, true);
                _delay_ms(1200);
            }        
            
        }
        else if(getLastVisitedSymbol() == DetectedSymbol::LED){     //LED symbol
            


            while(!(MakerLine::getDigitalInput3() || MakerLine::getDigitalInput2() || MakerLine::getDigitalInput4())){

                if(MakerLine::getDigitalInput1() && MakerLine::getDigitalInput2() && !MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED, MAX_SPEED - 20);
            
                }

                else if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5() && MakerLine::getDigitalInput4()){
                    Motor::turnForward(MAX_SPEED - 20, MAX_SPEED);
                    
                }

                else if(MakerLine::getDigitalInput1() && !MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED, MAX_SPEED - 15);
            
                }

                else if(!MakerLine::getDigitalInput1() && MakerLine::getDigitalInput5()){
                    Motor::turnForward(MAX_SPEED - 15, MAX_SPEED);
                    
                }
            }
            goToLine(1300, false);                                   //trouver le temps pour retrouver la ligne apres la detection de la diode ================================== 
            
        }
    

        if (MakerLine::allWhiteDetected()){
            Motor::stop();
            _delay_ms(100);
            Robot::findLine();
        } 
        symbolBehavior = true; 
    }
}



void Robot::start(){

        
    Timer1::startCounter(10);
    while(Timer1::getTimerCounter() < 200){
        if (button.isPressed()){
            Report::sendReportViaUART();
            while(true){}
        }
    }


    while(!redTape){

        followLine();

        if(symbolBehavior){  //expecting a pole or tape

            if(MakerLine::allWhiteDetected()){

                goToLine(TIME_TO_PASS_TAPE, false);    //false -> scan (findLine()) disabled     

                if(MakerLine::allWhiteDetected()){  //red tape
                    Motor::stop();
                    betweenSymbols[symbolVisitedCounter - 1] = BetweenSymbols::TAPE;
                    redTape = true;
                }
                else{                               //yellow tape
                    symbolBehavior = false;
                    betweenSymbols[symbolVisitedCounter - 1] = BetweenSymbols::TAPE;
                }
            }

            else if(DistanceSensor::past10Inches()){
                //Switch case qui depend de lastVisitedSymbol =========================================================================================================
                //call les methodes qui implementent les comportement devant les poteaux
                //pour avoir le dernier symbole visité il faut faire getLastVisitedSymbol()
            }

        }

        else if(MakerLine::allBlackDetected() || MakerLine::allWhiteDetected()){    // expecting to scan a symbol
            symbolDetection();

        }

    }
    Robot::led.green();
    // Methode qui implemente le comportement du tape rouge ================================================================================
    while(redTape){
        if(button.isPressed()){
            Report::saveReportInEeprom();
        }
    }
}






//==================================================================================================================================
//=============================== COMPORTEMENTS ====================================================================================
//==================================================================================================================================


void Robot::poleIfPiezo(){
//au debut on est a 10 pouces du poteau sur la ligne





//a la fin on traverse le tape jaune, on ajoute le poteau a betweenSymbols[symbolVisitedCounter - 1]
//set symbolBehavior = false;
}






void Robot::poleIfSwitch(){
//au debut on est a 10 pouces du poteau sur la ligne



//a la fin on traverse le tape jaune, on ajoute le poteau a betweenSymbols[symbolVisitedCounter - 1]
//set symbolBehavior = false;
}




void Robot::poleIfLed(){
//au debut on est a 10 pouces du poteau sur la ligne




//a la fin on traverse le tape jaune, on ajoute le poteau a betweenSymbols[symbolVisitedCounter - 1]
//set symbolBehavior = false;
}






void Robot::poleIfMotor(){
//au debut on est a 10 pouces du poteau sur la ligne





//a la fin on retrouve la ligne, on ajoute le poteau a betweenSymbols[symbolVisitedCounter - 1]
//set symbolBehavior = false;
}


void Robot::redTape(){
    while (redTape){
        if(button.isPressed()){
            Report::saveReportInEeprom();
        }


    // ajouter les trucs de led

    }

}