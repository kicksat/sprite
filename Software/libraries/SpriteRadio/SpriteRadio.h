/*
  SpriteRadio.h - An Energia library for transmitting data using the CC430 series of devices
  
  by Zac Manchester

*/

#ifndef SpriteRadio_h
#define SpriteRadio_h

#define SR_DEBUG_MODE 1

#define PRN_LENGTH_BYTES 64

#include "cc430radio.h"

class SpriteRadio {
  public:
	
	// Constructor - optionally supply radio register settings
	SpriteRadio(unsigned char prn0[], unsigned char prn1[]);
	SpriteRadio(unsigned char prn0[], unsigned char prn1[], CC1101Settings settings);
	
	// Set the transmitter power level. Default is 10 dBm.
	void setPower(int tx_power_dbm);

	// Transmit the given byte array as-is
    void rawTransmit(unsigned char bytes[], unsigned int length);

    // Encode the given byte with FEC and transmit
    void transmitByte(char byte);

    // Encode the given byte array with FEC and transmit
    void transmit(char bytes[], unsigned int length);

	// Initialize the radio - must be called before transmitting
    void txInit();

	// Put the radio in low power mode - call after transmitting
	void sleep();
	
	char fecEncode(char data);

  private:
	CC1101Settings m_settings;
	char m_power;
	unsigned char *m_prn0;
	unsigned char *m_prn1;
	
	void beginRawTransmit(unsigned char bytes[], unsigned int length);
	void continueRawTransmit(unsigned char bytes[], unsigned int length);
	void endRawTransmit();

};

#endif //SpriteRadio_h
