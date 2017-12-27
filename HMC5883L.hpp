/*
 * name:        HMC5883L
 * description: Surface-mount, multi-chip module designed for low-field magnetic sensing with a digital interface for applications such as lowcost compassing and magnetometry
 * manuf:       Honeywell
 * version:     0.1
 * url:         https://aerocontent.honeywell.com/aero/common/documents/myaerospacecatalog-documents/Defense_Brochures-documents/HMC5883L_3-Axis_Digital_Compass_IC.pdf
 * date:        2016-08-01
 * author       https://chisl.io/
 * file:        HMC5883L.hpp
 */

#include <cinttypes>

/* Derive from class HMC5883L_Base and implement the read and write functions! */

/* HMC5883L: Surface-mount, multi-chip module designed for low-field magnetic sensing with a digital interface for applications such as lowcost compassing and magnetometry */
class HMC5883L_Base
{
public:
	/* Pure virtual functions that need to be implemented in derived class: */
	virtual uint8_t read8(uint16_t address, uint16_t n=8) = 0;  // 8 bit read
	virtual void write(uint16_t address, uint8_t value, uint16_t n=8) = 0;  // 8 bit write
	virtual uint16_t read16(uint16_t address, uint16_t n=16) = 0;  // 16 bit read
	virtual void write(uint16_t address, uint16_t value, uint16_t n=16) = 0;  // 16 bit write
	virtual uint32_t read32(uint16_t address, uint16_t n=32) = 0;  // 32 bit read
	virtual void write(uint16_t address, uint32_t value, uint16_t n=32) = 0;  // 32 bit write
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG ConfigA                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG ConfigA:
	 * Configure the device for setting the data output rate and measurement configuration. 
	 */
	struct ConfigA
	{
		static const uint16_t __address = 0;
		
		/* Bits CRA7: */
		/* Reserved for future function. Set to 0 when configuring CRA.  */
		struct CRA7
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits MA: */
		/* Select number of samples averaged (1 to 8) per measurement output.  */
		struct MA
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b01100000; // [5,6]
			static const uint8_t MA_1 = 0b00; // Default 1 sample average/output
			static const uint8_t MA_2 = 0b01; // 2 sample average/output
			static const uint8_t MA_4 = 0b10; // 4 sample average/output
			static const uint8_t MA_8 = 0b11; // 8 sample average/output
		};
		/* Bits DO: */
		/*
		 * All selectable data output rates in continuous measurement mode. All three channels shall be measured
		 *           within a given output rate. Other output rates with maximum rate of 160 Hz can be achieved by
		 *           monitoring DRDY interrupt pin in single measurement mode. 
		 */
		struct DO
		{
			static const uint8_t dflt = 0b100; // 3'b100
			static const uint8_t mask = 0b00011100; // [2,3,4]
			static const uint8_t DO_0_75 = 0b00; // 0.75 Hz
			static const uint8_t DO_1_5 = 0b01; // 1.5 Hz
			static const uint8_t DO_3 = 0b10; // 3 Hz
			static const uint8_t DO_7_5 = 0b11; // 7.5 Hz
			static const uint8_t DO_15 = 0b100; // 15 Hz (Default)
			static const uint8_t DO_30 = 0b101; // 30 Hz
			static const uint8_t DO_75 = 0b110; // 75 Hz
			static const uint8_t reserved_0 = 0b111; // 
		};
		/* Bits MS: */
		/*
		 * The Measurement Configuration Bits define the measurement flow of the device,
		 *           specifically whether or not to incorporate an applied bias into the measurement. 
		 * 'b11 reserved. 
		 */
		struct MS
		{
			static const uint8_t dflt = 0b00; // 2'b0
			static const uint8_t mask = 0b00000011; // [0,1]
			static const uint8_t Normal = 0b00; // Normal measurement configuration (Default). In normal measurement configuration the device follows normal measurement flow. The positive and negative pins of the resistive load are left floating and high impedance.
			static const uint8_t Positive = 0b01; // Positive bias configuration for X, Y, and Z axes. In this configuration, a positive current is forced across the resistive load for all three axes.
			static const uint8_t Negative = 0b10; // Negative bias configuration for X, Y and Z axes. In this configuration, a negative current is forced across the resistive load for all three axes..
		};
	};
	
	/* Set register ConfigA */
	void setConfigA(uint8_t value)
	{
		write(ConfigA::__address, value, 8);
	}
	
	/* Get register ConfigA */
	uint8_t getConfigA()
	{
		return read8(ConfigA::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                           REG ConfigB                                            *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG ConfigB:
	 * Set the device gain. 
	 */
	struct ConfigB
	{
		static const uint16_t __address = 1;
		
		/* Bits GN: */
		/*
		 * The Gain Configuration Bits configure the gain for the device.
		 *           The gain configuration is common for all channels.
		 *           <br>Sensor field range / Gain (LSb/G) / digital resolution (mG/LSb) / Output range 
		 */
		struct GN
		{
			static const uint8_t dflt = 0b001; // 3'b1
			static const uint8_t mask = 0b11100000; // [5,6,7]
			static const uint8_t GN_1370 = 0b00; // +/- 0.88G / 1370 / 0.73    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_1090 = 0b01; // +/- 1.3G  / 1090 / 0.92    / 0xF800-0x07FF (-2048-2047 )  (default)
			static const uint8_t GN_820 = 0b10; // +/- 1.9G  /  820 / 1.22    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_660 = 0b11; // +/- 2.5G  /  660 / 1.52    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_440 = 0b100; // +/- 4.0G  /  440 / 2.27    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_390 = 0b101; // +/- 4.7G  /  390 / 2.56    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_330 = 0b110; // +/- 5.6G  /  330 / 3.03    / 0xF800-0x07FF (-2048-2047 )
			static const uint8_t GN_230 = 0b111; // +/- 8.1G  /  230 / 4.35    / 0xF800-0x07FF (-2048-2047 )
		};
		/* Bits reserved_0: */
		struct reserved_0
		{
			static const uint8_t dflt = 0b00000; // 5'b0
			static const uint8_t mask = 0b00011111; // [0,1,2,3,4]
		};
	};
	
	/* Set register ConfigB */
	void setConfigB(uint8_t value)
	{
		write(ConfigB::__address, value, 8);
	}
	
	/* Get register ConfigB */
	uint8_t getConfigB()
	{
		return read8(ConfigB::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                             REG Mode                                              *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Mode:
	 * Select operating mode of the device 
	 */
	struct Mode
	{
		static const uint16_t __address = 2;
		
		/* Bits HS: */
		/* enable High Speed I2C, 3400kHz  */
		struct HS
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b10000000; // [7]
		};
		/* Bits unused_0: */
		struct unused_0
		{
			static const uint8_t dflt = 0b00000; // 5'b0
			static const uint8_t mask = 0b01111100; // [2,3,4,5,6]
		};
		/* Bits MD: */
		struct MD
		{
			static const uint8_t dflt = 0b01; // 2'b1
			static const uint8_t mask = 0b00000011; // [0,1]
			/*
			 * Continuous-Measurement Mode. In continuous-measurement mode, the device continuously
			 *             - performs measurements and places the result in the data register.
			 *             - RDY goes high when new data is placed in all three registers. After a power-on or a
			 *             - write to the mode or configuration register, the first measurement set is available
			 *             - from all three data output registers after a period of 2/fDO and subsequent
			 *             - measurements are available at a frequency of fDO, where fDO is the frequency of data
			 *             - output. 
			 */
			static const uint8_t Continuous = 0b00;
			static const uint8_t Single = 0b01; // Single-Measurement Mode (Default). When single-measurement mode is selected, device performs a single measurement, sets RDY high and returned to idle mode. Mode register returns to idle mode bit values. The measurement remains in the data output register and RDY remains high until the data output register is read or another measurement is performed.
			static const uint8_t Idle1 = 0b10; // Device is placed in idle mode.
			static const uint8_t Idle2 = 0b11; // Device is placed in idle mode.
		};
	};
	
	/* Set register Mode */
	void setMode(uint8_t value)
	{
		write(Mode::__address, value, 8);
	}
	
	/* Get register Mode */
	uint8_t getMode()
	{
		return read8(Mode::__address, 8);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG DataOutputX                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG DataOutputX:
	 * These registers store the measurement result from channel X.
	 *       The value stored in these two registers is a 16-bit value in 2's complement form, whose range is
	 *       0xF800 to 0x07FF. 
	 */
	struct DataOutputX
	{
		static const uint16_t __address = 3;
		
		/* Bits DataOutputX: */
		struct DataOutputX_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register DataOutputX */
	void setDataOutputX(uint16_t value)
	{
		write(DataOutputX::__address, value, 16);
	}
	
	/* Get register DataOutputX */
	uint16_t getDataOutputX()
	{
		return read16(DataOutputX::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG DataOutputZ                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG DataOutputZ:
	 * These registers store the measurement result from channel Z. 
	 */
	struct DataOutputZ
	{
		static const uint16_t __address = 5;
		
		/* Bits DataOutputZ: */
		struct DataOutputZ_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register DataOutputZ */
	void setDataOutputZ(uint16_t value)
	{
		write(DataOutputZ::__address, value, 16);
	}
	
	/* Get register DataOutputZ */
	uint16_t getDataOutputZ()
	{
		return read16(DataOutputZ::__address, 16);
	}
	
	
	/****************************************************************************************************\
	 *                                                                                                  *
	 *                                         REG DataOutputY                                          *
	 *                                                                                                  *
	\****************************************************************************************************/
	
	/*
	 * REG DataOutputY:
	 * These registers store the measurement result from channel Y. 
	 */
	struct DataOutputY
	{
		static const uint16_t __address = 7;
		
		/* Bits DataOutputY: */
		struct DataOutputY_
		{
			/* Mode:r */
			static const uint16_t mask = 0b1111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
		};
	};
	
	/* Set register DataOutputY */
	void setDataOutputY(uint16_t value)
	{
		write(DataOutputY::__address, value, 16);
	}
	
	/* Get register DataOutputY */
	uint16_t getDataOutputY()
	{
		return read16(DataOutputY::__address, 16);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                            REG Status                                             *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Status:
	 * Indicate the device status. 
	 */
	struct Status
	{
		static const uint16_t __address = 9;
		
		/* Bits reserved_0: */
		struct reserved_0
		{
			static const uint8_t dflt = 0b000000; // 6'd0
			static const uint8_t mask = 0b11111100; // [2,3,4,5,6,7]
		};
		/* Bits LOCK: */
		/*
		 * Data output register lock. This bit is set when:
		 *           1. some but not all for of the six data output registers have been read,
		 *           2. Mode register has been read.
		 *           When this bit is set, the six data output registers are locked and any new data will not be placed in these register until one of these conditions are met:
		 *           1. all six bytes have been read,
		 *           2. the mode register is changed,
		 *           3. the measurement configuration (CRA) is changed,
		 *           4. power is reset. 
		 */
		struct LOCK
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000010; // [1]
		};
		/* Bits RDY: */
		/*
		 * Ready Bit. Set when data is written to all six data registers. Cleared when device initiates a write to the data output registers and after one or more of the data output registers are written to. When RDY bit is clear it shall remain cleared for a 250 μs.
		 *           DRDY pin can be used as an alternative to the status register for monitoring the device for measurement data. 
		 */
		struct RDY
		{
			static const uint8_t dflt = 0b0; // 1'b0
			static const uint8_t mask = 0b00000001; // [0]
		};
	};
	
	/* Set register Status */
	void setStatus(uint8_t value)
	{
		write(Status::__address, value, 8);
	}
	
	/* Get register Status */
	uint8_t getStatus()
	{
		return read8(Status::__address, 8);
	}
	
	
	/*****************************************************************************************************\
	 *                                                                                                   *
	 *                                        REG Identification                                         *
	 *                                                                                                   *
	\*****************************************************************************************************/
	
	/*
	 * REG Identification:
	 * The identification value for this device is stored in this register. 
	 */
	struct Identification
	{
		static const uint16_t __address = 16;
		
		/* Bits Identification: */
		struct Identification_
		{
			/* Mode:r */
			static const uint32_t dflt = 0b010010000011010000110011; // 24'b10010000011010000110011
			static const uint32_t mask = 0b111111111111111111111111; // [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]
		};
	};
	
	/* Set register Identification */
	void setIdentification(uint32_t value)
	{
		write(Identification::__address, value, 24);
	}
	
	/* Get register Identification */
	uint32_t getIdentification()
	{
		return read32(Identification::__address, 24);
	}
	
};
