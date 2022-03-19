#define ADDRESS 0b11010000

enum i2cDirection {
    READ,
    WRITE    
};

void sendSLA(char direction) {
	TWDR = ADDRESS | direction;
	TWCR &= ~(1<<TWSTA);
	TWCR |= (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	while(!(TWSR & (direction == 0 ? 0x40 : 0x18)));//ACK+SLAW/R CHECK
}

void writeStartCondition(void) {
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); //WRITE START CONDITION
	while(!(TWCR & (1<<TWINT)));                
	while(!((TWSR & 0x08) || (TWSR & 0x10)));	//WAIT FOR RIGHT STATUS, SEE DATASHEET
}

void sendByte(unsigned char data) {
	TWDR = data;
	TWCR |= (1<<TWINT);
	while(!(TWCR & (1<<TWINT)));
	while(!(TWSR & 0x28));//ACK+DATA CHECK	
}

unsigned char getByte() {
    TWCR |= (1<<TWEA) | (1<<TWINT);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}

void writeStopCondition(void){
	while(!(TWCR & (1<<TWINT)));
	TWCR |= (1<<TWINT) | (1<<TWEN) |(1<<TWSTO);
}

int readRegisters(unsigned char *data){ 
    writeStartCondition();
    
    sendSLA(WRITE);
    sendByte(0); // register ptr = 0
    writeStopCondition();
    writeStartCondition();
    sendSLA(READ);
    
    for(unsigned char i = 0; i < 8; i++){
        data[i] = getByte();
    }

    writeStopCondition();
}

int writeRegister(unsigned char at, unsigned char data){
    writeStartCondition();
    sendSLA(WRITE);
    sendByte(at);
    sendByte(data);
    writeStopCondition();
}