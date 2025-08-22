#include <iostream>
#include <string>
#include <vector>

enum class OrderType: char {
    MARKET = 'M',
    LIMIT = 'L',
    STOP = 'S'
};

struct Order {
    int orderId;
    std::string symbol;
    int quantity;
    double price;
    OrderType orderType;

    // Constructor validation
    // Make sure the orderType is either 'M', 'L', or 'S'
    Order(int id, const std::string& sym, int qty, double prc, OrderType type)
        : orderId(id), symbol(sym), quantity(qty), price(prc), orderType(type) {
        if (type != OrderType::MARKET && type != OrderType::LIMIT && type != OrderType::STOP) {
            throw std::invalid_argument("Invalid order type");
        }

        // Check if prise is positive
        if (prc <= 0) {
            throw std::invalid_argument("Price must be positive");
        }

        // Check if quantity is positive
        if (qty > 100000 || qty < 1) {
            throw std::invalid_argument("Quantity must be between 1 and 100000");
        }

        // Symbol must be 8 chars max
        if (sym.length() > 8) {
            throw std::invalid_argument("Symbol must be 8 chars max");
        }
    }
};

class OrderProcessingSystem {
    private:
        std::vector<Order> orders;

    public:
        // Use switch case to print order details with modern c++
        void executeOrder(const Order& order) {
            switch (order.orderType) {
                case OrderType::MARKET:
                    std::cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol << ", Quantity: " << order.quantity << ", Price: " << order.price << ", Order Type: Market" << std::endl;
                    break;
                case OrderType::LIMIT:
                    std::cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol << ", Quantity: " << order.quantity << ", Price: " << order.price << ", Order Type: Limit" << std::endl;
                    break;
                case OrderType::STOP:
                    std::cout << "Order ID: " << order.orderId << ", Symbol: " << order.symbol << ", Quantity: " << order.quantity << ", Price: " << order.price << ", Order Type: Stop" << std::endl;
                    break;
                default:
                    std::cout << "Invalid order type" << std::endl;
                    break;
            }
        }

        // Add order to the system
        void addOrder(const Order& order) {
            orders.push_back(order);
        }

        // Get order by id
        Order getOrderById(int id) {
            for (const auto& order : orders) {
                if (order.orderId == id) {
                    return order;
                }
            }
            throw std::invalid_argument("Order not found");
        }

        // Get order by symbol
        Order getOrderBySymbol(const std::string& symbol) {
            for (const auto& order : orders) {
                if (order.symbol == symbol) {
                    return order;
                }
            }
            throw std::invalid_argument("Order not found");
        }
};

void populateOrders(OrderProcessingSystem& orderProcessingSystem) {
    orderProcessingSystem.addOrder(Order(1, "AAPL", 100, 150.0, OrderType::MARKET));
    orderProcessingSystem.addOrder(Order(2, "GOOG", 200, 2500.0, OrderType::LIMIT));
    orderProcessingSystem.addOrder(Order(3, "MSFT", 300, 350.0, OrderType::STOP));
}

int main() {
    OrderProcessingSystem orderProcessingSystem;
    populateOrders(orderProcessingSystem);
    orderProcessingSystem.executeOrder(orderProcessingSystem.getOrderById(1));
    orderProcessingSystem.executeOrder(orderProcessingSystem.getOrderById(2));
    orderProcessingSystem.executeOrder(orderProcessingSystem.getOrderById(3));
    return 0;
}