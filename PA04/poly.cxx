#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	polynomial::polynomial(double c, unsigned int exponent)
	{
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if(fabs(c) < EPSILON)
		{
			head_ptr = new polynode();
			tail_ptr = head_ptr;
			recent_ptr = head_ptr;
			current_degree = 0;
		}
		else{
			if(exponent == 0)
			{
				tail_ptr = new polynode(c, exponent);
				tail_ptr = head_ptr;
				recent_ptr = head_ptr;
				current_degree = 0;
			}
			else{
				head_ptr = new polynode();
				tail_ptr = new polynode(c, exponent, nullptr, head_ptr);
				head_ptr->set_fore(tail_ptr);
				recent_ptr = tail_ptr;
				current_degree = exponent;
			}
		}
    }

    polynomial& polynomial::operator=(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		if(this == &source)
		{
			return *this;
		}
		clear();
		polynode *sourceRecent = source.recent_ptr;
		head_ptr->set_coef(0.0);
		recent_ptr = head_ptr;
		current_degree = 0;
		source.set_recent(0);
		
		//Need to make first item in the poly them same
		
		recent_ptr->set_coef(source.recent_ptr->coef());
		source.recent_ptr = source.recent_ptr->fore();
		
		polynode *temp;
		while(source.recent_ptr != nullptr)
		{
			temp = new polynode(source.recent_ptr->coef(), source.recent_ptr->exponent(), nullptr, recent_ptr);
			recent_ptr->set_fore(temp);
			recent_ptr = temp;
			tail_ptr = temp;
			source.recent_ptr = source.recent_ptr->fore();
		}
		current_degree =  tail_ptr->exponent();
		source.recent_ptr = sourceRecent;
		return *this;
	}
	
    polynomial::polynomial(const polynomial& source)
    {
		// store machine epsilon
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode();
		tail_ptr = head_ptr;
		recent_ptr = head_ptr;
		current_degree = 0;
		*this = source;
    }
	
    polynomial::~polynomial()
    {
		clear();
		current_degree = 0;
		delete head_ptr;
		head_ptr = nullptr;
		tail_ptr = nullptr;
		recent_ptr = nullptr;
    }

    void polynomial::clear()
    {
		polynode* temp = head_ptr;
		while (head_ptr->fore() != nullptr)
		{
			temp = head_ptr->fore();
			head_ptr->set_fore(temp->fore());
			delete temp;
		}
		tail_ptr = head_ptr;
		current_degree = 0;
		
    }
    
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		if(recent_ptr->exponent() == exponent)
		{
			return recent_ptr->coef();
		}
		return 0;
    }
    

    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
		set_recent(exponent);
		if(recent_ptr->exponent() == exponent)
		{
			double current_coef = recent_ptr->coef();
			assign_coef((current_coef + amount), exponent);
		}
		else{
			assign_coef(amount, exponent);
		}
	}

    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		set_recent(exponent);
		if(fabs(coefficient) >= EPSILON)
		{
			if(recent_ptr->exponent() == exponent)
			{
				recent_ptr->set_coef(coefficient);
			}
			else{
				if(recent_ptr->fore() != nullptr)
				{
					polynode *temp = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
					recent_ptr->fore()->set_back(temp);
					recent_ptr->set_fore(temp);
				}
				else{
					polynode *temp = new polynode(coefficient, exponent, nullptr, recent_ptr);
					recent_ptr->set_fore(temp);
					tail_ptr = temp;
				}
			}
		}
		else{
			if(recent_ptr->exponent() == exponent)
			{
				if(head_ptr != recent_ptr)
				{
					if(recent_ptr->fore() != nullptr)
					{
						recent_ptr->back()->set_fore(recent_ptr->fore());
						recent_ptr->fore()->set_back(recent_ptr->back());
						delete recent_ptr;
					}
					else{
						set_recent(recent_ptr->back()->exponent());
						delete recent_ptr->fore();
						recent_ptr->set_fore(nullptr);
						tail_ptr = recent_ptr;
					}
				}
				else{
					head_ptr->set_coef(0.0);
				}	
			}
		}
		current_degree = tail_ptr->exponent();
	}

    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		set_recent(exponent);
		if(recent_ptr->fore() != nullptr)
		{
			return recent_ptr->fore()->exponent();
		}
		return 0;
    }

	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if(exponent == 0)
		{
			return UINT_MAX;	
		}
		set_recent(exponent);
		if(recent_ptr->exponent() < exponent)
		{
			
			if(recent_ptr == head_ptr && fabs(recent_ptr->coef()) >= EPSILON)
			{
				return 0;
			}
			if (recent_ptr == head_ptr && fabs(recent_ptr->coef()) < EPSILON){
			
				return UINT_MAX;
			}
			return recent_ptr->exponent();
		}
		else{
			if (recent_ptr->back()->coef() == 0)
				return UINT_MAX;
			return recent_ptr->back()->exponent();
		}
    }

    void polynomial::set_recent(unsigned int exponent) const
    {
		if (exponent == 0)
		{
			recent_ptr = head_ptr;
			return;
		}
		
		if (exponent >= current_degree)
		{
			recent_ptr = tail_ptr;
			return;
		}
		
		if (exponent > recent_ptr->exponent())
		{
			while (recent_ptr->fore()->exponent() <= exponent)
			{
				recent_ptr = recent_ptr->fore();
			}
		}
		if (exponent < recent_ptr->exponent())
		{
			while (recent_ptr->back()->exponent() >= exponent)
			{
				recent_ptr = recent_ptr->back();
			}
			if (recent_ptr->exponent() != exponent)
				recent_ptr = recent_ptr->back();
		}
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		set_recent(0);
		while(recent_ptr != nullptr)
		{
			total += pow(x, recent_ptr->exponent()) * recent_ptr->coef();
			recent_ptr = recent_ptr->fore();
		}
		return total;
    }

    polynomial polynomial::derivative() const
    {
		
		polynomial p_prime;
		set_recent(0);
		while(recent_ptr != nullptr)
		{
			if(recent_ptr->exponent() != 0)
			{
				p_prime.assign_coef(recent_ptr->coef() * recent_ptr->exponent(), recent_ptr->exponent()-1);
			}
			recent_ptr = recent_ptr->fore();
		}
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		unsigned int term = 0;
		p.assign_coef(p1.coefficient(0), 0);
		term = p1.next_term(term);
		while(term != 0)
		{
			p.assign_coef(p1.coefficient(term), term);
			term = p1.next_term(term);
		}
		term = 0;
		p.add_to_coef(p2.coefficient(0), 0);
		term = p2.next_term(term);
		while(term != 0)
		{
			p.add_to_coef(p2.coefficient(term), term);
			term = p2.next_term(term);
		}
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		polynomial p;
		unsigned int term = 0;
		p.assign_coef(p1.coefficient(0), 0);
		term = p1.next_term(term);
		while(term != 0)
		{
			p.assign_coef(p1.coefficient(term), term);
			term = p1.next_term(term);
		}
		term = 0;
		p.add_to_coef(-1*p2.coefficient(0), 0);
		term = p1.next_term(term);
		while(term != 0)
		{
			p.add_to_coef(-1*p2.coefficient(term), term);
			term = p2.next_term(term);
		}
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		unsigned int p1Term = 0;
		unsigned int p2Term = 0;
		unsigned int temp1 = 0;
		unsigned int temp2 = 0;	
		while(p1Term > 0 || temp1 == 0)
		{
			while(p2Term > 0 || temp2 == 0)
			{
				p.add_to_coef(p1.coefficient(p1Term)*p2.coefficient(p2Term), p1Term+p2Term);
				p2Term = p2.next_term(p2Term);
				temp2++;
			}
			temp2 = 0;
			temp1++;
			p1Term = p1.next_term(p1Term);
		}
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		do
		{
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0) out << " + ";
		} while(expo != 0);
		return out;
    }
    
    void polynomial::find_root(double& answer, bool& success, unsigned int& iterations, double guess, unsigned int maximum_iterations, double epsilon) const
    {
		answer = guess;
		iterations = 0;
		
		while(fabs(eval(answer)) >= epsilon && fabs(derivative().eval(answer)) >= epsilon && iterations < maximum_iterations)
		{
			answer = answer - ((eval(answer)) / (derivative().eval(answer)));
			iterations++;
		}
		cout << "Iterations: " << iterations << endl;
		cout << "Max Iterations: " << maximum_iterations << endl;
		cout << "Answer: " << answer << endl;
		if(iterations == maximum_iterations || derivative().eval(answer) < epsilon)
		{
			if(derivative().eval(answer) < epsilon)
			{
				cout << "Failed because this function was a flat function" << endl;
				success = false;
			}
			if(iterations == maximum_iterations)
			{
				cout << "Failed because method reached maximum iterations" << endl;
				success = false;
			}
		}
		else{
			cout << "Success!" << endl;
			success = true;
		}
	}
}
