#include "commons.h"
#include "math.h"
#include "zxLib.h"[]
//Mixture_Nonmatch:DualTask_Nonmatch+DNMS; Mixture_Match:DualTask_match+DNMS; HZ_Go2:????SpHit3; HZ_DNMS_Match:Match-go??DualTask2:Go/no-go????Reward,reward??????
//////////////HZ functions/////////////
void licksend(float timelen);
void HZ_go(int trialNum, int waterLen, int autoWater);
void DMN(int trialNum, int waterLen, int autoWater);
void motor(int protoL, int protoR, int type, int yesLeft, int yesRight);
void feedWater(int waterLength);
void feedWaterNew(void);
void testPort(void);


static int waterSize[] = {110, 90, 90, 60, 110, 120, 130, 120};
int motorYes = 0;

void FuncID(int n) {
    switch (n) {
        case 1:
        { //run water pump 
            Valve_ON(1);
        }
            break;
        case 2:
        { // feed water auto
            //int laserHigh = getFuncNumber(3);
            //int laserLow = getFuncNumber(3);
            feedWater(100);
            int calidir = getFuncNumber(1);
            calidir = 1;
        }
            break;
        case 3:
        { // test odor concentration
            testPort();
        }
            break;
        case 4:
        {// auto water on
            int numTrialPerSess = 12;
            int numSess = 10;
            int numThisSess = 0;
            while (numThisSess < numSess) {
                serialSend(SpSess, 1);
                HZ_go(numTrialPerSess, 100, 1);
                serialSend(SpSess, 0);
                numThisSess = numThisSess + 1;
            }
            break;
        }
        case 5:
        {// auto water off
            int numTrialPerSess = 12;
            int numSess = 10;
            int numThisSess = 0;
            while (numThisSess < numSess) {
                serialSend(SpSess, 1);
                HZ_go(numTrialPerSess, 100, 0);
                serialSend(SpSess, 0);
                numThisSess = numThisSess + 1;
            }
            break;
        }
        case 6: // test water volume
        {
            unsigned int a = 0;
            int waterSizeInd = getFuncNumber(1) - 1;
            while (a < 20) {
                wait_ms(1000);
                Valve_ON(1);
                wait_ms(waterSize[waterSizeInd]);
                Valve_OFF(1);
                a++;
            }
        }
            break;
        case 7: //test lick detection
        {
            while (1) {
                serialSend(17, analogRead(6) / 10);
                delay(1000);
            }
            break;
        }
		case 8: //DMN 2-odor task (auto water on)
		{
			int numTrialPerSess = 12;
			int numSess = 10;
			int numThisSess = 0;
			while (numThisSess < numSess) {
				serialSend(SpSess, 1);
				DMN(numTrialPerSess, 100, 1);
				serialSend(SpSess, 0);
				numThisSess = numThisSess + 1;
			}
			break;
		}
		case 9: //DMN 2-odor task (auto water off)
		{
			int numTrialPerSess = 14;
			int numSess = 10;
			int numThisSess = 0;
			while (numThisSess < numSess) {
				serialSend(SpSess, 1);
				DMN(numTrialPerSess, 100, 0);
				serialSend(SpSess, 0);
				numThisSess = numThisSess + 1;
			}
			break;
		}
    }
}

void DMN(int trialNum, int waterLen, int autoWater) {
	 int trialId = 0;
	
	while (trialId < trialNum) {
		wait_ms(19000);
		Valve_ON(odor_A);
		serialSend(SpOdor, odor_A);
		wait_ms(1000);
		Valve_OFF(odor_A);
		serialSend(SpOdor,odor_A);
		wait_ms(4000);
		////////////////////////////
		hasLicked = 0;
		////////////////////////////
		
		Valve_ON(odor_C);
		serialSend(SpOdor, odor_C);



		unsigned long millisT = millis();
		unsigned long whenLick;
		while (millis() - millisT < 500 && !hasLicked){
			hasLicked = isLicking;
			whenLick = millis();
		}
		unsigned long restOdorTime = 500-(whenLick - millisT);
		if (restOdorTime > 0) {
			wait_ms(restOdorTime);
			Valve_OFF(odor_C);
			serialSend(SpOdor, odor_C);
		}
		else {
			Valve_OFF(odor_C);
			serialSend(SpOdor, odor_C);
		}
		if (autoWater&&trialId % 3 == 0) {
			Valve_ON(1);
			wait_ms(waterLen);
			Valve_OFF(1);
		}
		if (!hasLicked) {
			currentMiss++;
			serialSend(SpMiss, 1);
		}
		else {
			Valve_ON(1);
			wait_ms(waterLen);
			Valve_OFF(1);
			currentMiss = 0;
			serialSend(SpHit, 1);
		}
	}
}

void HZ_go(int trialNum, int waterLen, int autoWater) {
    //waitTrial();
    int odorLen = 1000;
    int odorIn = odor_A;
    int trialId=0;
    /////////////////////////
    while (trialId < trialNum) {
        Valve_ON(odorIn);
        serialSend(SpOdor, odorIn);
        wait_ms(odorLen);
        Valve_OFF(odorIn);
        serialSend(SpOdor, odorIn);
        ///////////////////////////
        hasLicked = 0;
        /////////////////
        if (autoWater&&trialId%3==0) {
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
        }
        unsigned long millisT = millis();
        while (millis() - millisT < 1000 && !hasLicked) {
            hasLicked = isLicking;
        }
        if (!hasLicked) {
            currentMiss++;
            serialSend(SpMiss, 1);
        } else {
            Valve_ON(1);
            wait_ms(waterLen);
            Valve_OFF(1);
            currentMiss = 0;
            serialSend(SpHit, 1);
        }
        ////////////////////////////
        trialId++;
        srand(millis());
        wait_ms(12000+(rand()%2)*3000);//12 15 seconds
    }

}

void motor(int protoL, int protoR, int type, int yesLeft, int yesRight) {
    int motorLShort = protoL, motorRShort = protoR,
            motorLLong = protoL + 100, motorRLong = protoR + 100,
            motorL, motorR;
    if (yesLeft + yesRight > 0) {
        if (type == 1) { //1 shortForward 2 shortBackward
            motorL = motorLShort;
            motorR = motorRShort;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(46, HIGH);
                }
                if (yesRight) {
                    digitalWrite(48, HIGH);
                }
                wait_ms(motorL);
                digitalWrite(46, LOW);
                wait_ms(motorR - motorL);
                digitalWrite(48, LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(46, HIGH);
                }
                if (yesRight) {
                    digitalWrite(48, HIGH);
                }
                wait_ms(motorR);
                digitalWrite(48, LOW);
                wait_ms(motorL - motorR);
                digitalWrite(46, LOW);
            }
        } else if (type == 2) { //1 shortForward 2 shortBackward
            motorL = motorLShort;
            motorR = motorRShort;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(47, HIGH);
                }
                if (yesRight) {
                    digitalWrite(49, HIGH);
                }
                wait_ms(motorL + 10);
                digitalWrite(47, LOW);
                wait_ms(motorR - motorL + 10);
                digitalWrite(49, LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(47, HIGH);
                }
                if (yesRight) {
                    digitalWrite(49, HIGH);
                }
                wait_ms(motorR + 10);
                digitalWrite(49, LOW);
                wait_ms(motorL - motorR + 10);
                digitalWrite(47, LOW);
            }
        } else if (type == 3) {//3 longForward 4 longBackward
            motorL = motorLLong;
            motorR = motorRLong;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(46, HIGH);
                }
                if (yesRight) {
                    digitalWrite(48, HIGH);
                }
                wait_ms(motorL);
                digitalWrite(46, LOW);
                wait_ms(motorR - motorL);
                digitalWrite(48, LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(46, HIGH);
                }
                if (yesRight) {
                    digitalWrite(48, HIGH);
                }
                wait_ms(motorR);
                digitalWrite(48, LOW);
                wait_ms(motorL - motorR);
                digitalWrite(46, LOW);
            }
        } else if (type == 4) {//3 longForward 4 longBackward
            motorL = motorLLong;
            motorR = motorRLong;
            if (motorL <= motorR) {
                if (yesLeft) {
                    digitalWrite(47, HIGH);
                }
                if (yesRight) {
                    digitalWrite(49, HIGH);
                }
                wait_ms(motorL + 10);
                digitalWrite(47, LOW);
                wait_ms(motorR - motorL + 10);
                digitalWrite(49, LOW);
            } else {
                if (yesLeft) {
                    digitalWrite(47, HIGH);
                }
                if (yesRight) {
                    digitalWrite(49, HIGH);
                }
                wait_ms(motorR + 10);
                digitalWrite(49, LOW);
                wait_ms(motorL - motorR + 10);
                digitalWrite(47, LOW);
            }
        }
    }
}

void feedWater(int waterLength) {
    int wasLicking = 0;
    int lickCounter = 0;
    int interWater = 20000;
    int stopLoop = 0, numLoop = 0;
    //unsigned int timerAll = 0;
    while (!stopLoop && numLoop < 2) {
        Valve_ON(1);
        wait_ms(200);
        Valve_OFF(1);
        wait_ms(1000);
        Valve_ON(1);
        wait_ms(100);
        Valve_OFF(1);
        unsigned long millisT = millis();
        // while (timerAll < 20000 && millis()-millisT < interWater) {
        while (1) {
            if (isLicking && !wasLicking) {
                if (lickCounter % 3 == 0) {
                    Valve_ON(1);
                    //timerAll = timerAll + millis()-millisT;
                    millisT = millis();
                    interWater = 10000;
                    serialSend(SpHit, 1);
                }
                wasLicking = 1;
                lickCounter++;
                if (lickCounter > 10) {
                    stopLoop = 1;
                }
            } else if (wasLicking && !isLicking) {
                wasLicking = 0;
            }
            if (millis() - millisT > waterLength) {
                Valve_OFF(1);
            }
        }
        numLoop++;
        Valve_OFF(1);
    }
    Valve_OFF(1);
}

void feedWaterNew(void) {
    int waterLength = 40;
    int wasLicking = 0;
    int lickCounter = 0;
    unsigned long millisT = millis();
    Valve_ON(1);
    wait_ms(200);
    Valve_OFF(1);
    while (lickCounter < 5) {
        if (isLicking && !wasLicking) {
            millisT = millis();
            if (lickCounter % 3 == 0) {
                Valve_ON(1);
            }
            wasLicking = 1;
            lickCounter++;
        } else if (wasLicking && !isLicking) {
            wasLicking = 0;
        }
        if (millis() - millisT > waterLength) {
            Valve_OFF(1);
        }
    }
    Valve_OFF(1);
}

void testPort(void) {
    int i = 1;
    i = getFuncNumber(1);
    while (i) {
        // i = getFuncNumber(1, "Port:1-8");
        Valve_ON(i);
        serialSend(SpOdor, i);
        digitalWrite(38, HIGH);
        //DelayNmSecNew(4000);
        if (i == 4) {
            wait_ms(20000u);
        } else {
            wait_ms(1000u);
        }
        Valve_OFF(i);
        serialSend(SpOdor, i);
        digitalWrite(38, LOW);
        wait_ms(4000u);
    }
}



