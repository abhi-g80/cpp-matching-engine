#include <string>
#include <ostream>

class IDGenerator
{
	private:
		uint64_t order_id;
		uint64_t trade_id;
		uint32_t market_id; // currently market_id equals instrument.id

	public:
		IDGenerator(uint32_t market_id)
		{
			this->order_id = 0;
			this->trade_id = 0;
			this->market_id = market_id;
		}

		uint64_t generate_order_id(uint32_t market_id)
		{
			if (this->market_id != 0)
			{
				++order_id;
				return order_id;
			}
			else
			{
				throw std::logic_error("Market ID not defined.");
			}
		}

		uint64_t generate_trade_id(uint32_t market_id)
		{
			if (this->market_id != 0)
			{
				++trade_id;
				return trade_id;
			}
			else
			{
				throw std::logic_error("Market ID not defined.");
			}
		}
};