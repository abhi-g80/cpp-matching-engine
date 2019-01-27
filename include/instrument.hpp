#include <string>
#include <ostream>

using string = std::string;

class Instrument
{
    public:
        Instrument(uint32_t id, string symbol)
        {
            this->id = id;
            this->symbol = symbol;
        }

        uint32_t get_instrument_id() const { return this->id; }
        string get_instrument_symbol() const { return this->symbol; }
        
        friend std::ostream& operator<<( std::ostream&, const Instrument& );

    private:
        uint32_t id;
        string symbol;
};

inline std::ostream& operator<<( std::ostream& ostream, const Instrument& instrument )
{
  return ostream
         << "InstrumentID: " << instrument.get_instrument_id() << ", "
         << "InstrumentSymbol: " << instrument.get_instrument_symbol() << std::endl;
}

