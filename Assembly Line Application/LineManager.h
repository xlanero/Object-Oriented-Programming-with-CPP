#include <vector>
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace sict
{
	/**
	* Contains all the functionality for processing customer orders across the entire assembly line
	* The LineManager moves orders along the assemblyLine one step at a time
	*/
	class LineManager
	{
		std::vector<Station*> m_stationAddresses;
		std::vector<size_t> m_indexNextStation;

		// deque containers to help manipulate ordering
		std::deque<Station*> m_stations;
		std::deque<CustomerOrder> m_complete;
		std::deque<CustomerOrder> m_incomplete;
		std::deque<CustomerOrder> m_ordersToFill;
		
		size_t m_indexStartingStation;
		size_t m_indexLastStation;
		std::vector<size_t> m_stationOrder;
		/*size_t createAssemblyOrder(std::vector<size_t>&, size_t);*/

	public:

		LineManager(std::vector<Station*>&, std::vector<size_t>&, std::vector<CustomerOrder>&, size_t, std::ostream&);
		void display(std::ostream&) const;
		bool run(std::ostream&);

	};
}
