#include <algorithm>
#include <vector>
#include "Station.h"
#include "LineManager.h"

namespace sict
{
		LineManager::LineManager(std::vector<Station*>& stationAddresses, std::vector<size_t>& indexNextStation, std::vector<CustomerOrder>& customerOrders, size_t indexStartingStation, std::ostream& os)
		: m_indexStartingStation(indexStartingStation)
	{
		// add the customer orders to a queue
		for (auto& i : customerOrders) {
			m_ordersToFill.push_back(std::move(i));
		}

		// updates the vector to the order that the stations will be processed and returns the index of the last station
		m_stationOrder.push_back(indexStartingStation);

		for (size_t i = 0; i < indexNextStation.size(); i++) {

			m_stationOrder.push_back(indexNextStation[indexStartingStation]);
			indexStartingStation = indexNextStation[indexStartingStation];
		}

		m_stationOrder.front();

		/*m_indexLastStation = createAssemblyOrder(indexNextStation, indexStartingStation);*/

		// change m_stationAddresses to be in order
		for (size_t i = 0; i < stationAddresses.size(); ++i) {
			m_stations.push_back(stationAddresses[m_stationOrder[i]]);
			m_stationAddresses.push_back(stationAddresses[m_stationOrder[i]]);
		}
	}


	void LineManager::display(std::ostream& os) const {

		os << "COMPLETED ORDERS" << std::endl;

		//uses completed deque continer to display completed orders
		for (auto& i : m_complete) { 
			//calls CustomerOrder display
			i.display(os, true); 
		}

		os << std::endl << "INCOMPLETE ORDERS" << std::endl;

		// uses incompleted deque container to display incompleted orders
		for (auto& i : m_incomplete) { 
			//calls CustomerOrder display
			i.display(os, true); 
		}
	}

	bool LineManager::run(std::ostream& os) {

		// variable that holds how many remaining orders need to be filled
		size_t remainingItems = m_ordersToFill.size();
		// bool variable to determine completion
		bool endStatus = false;

		// while there are items that are waiting to be filled
		while (!m_ordersToFill.empty() || remainingItems) {

			// move order to the starting station
			*m_stationAddresses[0] += std::move(m_ordersToFill.front());
			// remove from ordersToFill deque container
			m_ordersToFill.pop_front();

			// loops through the stationAddresses and fills the incomplete orders
			for (auto& s : m_stationAddresses) {
				s->fill(os);
			}


			size_t index = m_indexStartingStation;
			// temporary CustomerOrder object
			CustomerOrder temp;

			// loops through the stationAddresses
			for (auto& s : m_stationAddresses) {

				// if there is an order to release
				if (s->hasAnOrderToRelease()) {

					//
					s->pop(temp);

					// if the iteration is not at the end of the stationAddresses container
					if (s != m_stationAddresses.back()) {

						//contain the address of the next position in a variable
						auto obj = *(&s + 1);
						// store the names of each position for displaying to os
						std::string prev = s->getName();
						std::string next = obj->getName();
						/*std::string prodName = temp.getNameProduct();*/
						*obj += std::move(temp);
						os << " --> " << temp.getNameProduct() << " moved from " << prev << " to " << next;
					}

					else {

						std::string prev = s->getName();
						os << " --> " << temp.getNameProduct() << " moved from " << prev << " to ";

						// if it is filled
						if (temp.isFilled()) {

							os << "Complete Set" << std::endl;
							m_complete.push_back(std::move(temp));
						}
						//if not filled
						else {
							os << "Incomplete Set" << std::endl;
							m_incomplete.push_back(std::move(temp));
						}
						// reduce the remaining items by 1
						--remainingItems;
					}
				}
			}
		}

		//if there are no more remaining items, return true i.e. completed
		if (!remainingItems) {

			endStatus = true;
		}

		return endStatus;
	}

	/*
	size_t LineManager::createAssemblyOrder(std::vector<size_t>& indexNextStation, size_t indexStartingStation) {

		m_stationOrder.push_back(indexStartingStation);

		for (auto i = 0; i < indexNextStation.size(); i++) {

			m_stationOrder.push_back(indexNextStation[indexStartingStation]);
			indexStartingStation = indexNextStation[indexStartingStation];
		}

		return m_stationOrder.front();
	}*/
}