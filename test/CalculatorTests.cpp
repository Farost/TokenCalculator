#include <gtest/gtest.h>
#include "../include/calculator.h"

bool testCalcStr(const std::string& str) {
    std::istringstream istr(str);
    return Calculator::get().calcExpression(istr);
}


float testGetRes() {
    return Calculator::get().getResult();
}


TEST(CalculatorTest, BlankTest) {
    {
        std::string str = "";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = " ";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "                          ";
        EXPECT_FALSE(testCalcStr(str));
    }
}


TEST(CalculatorTest, SumTest) {
    {
        std::string str = "+";
        EXPECT_FALSE(testCalcStr(str));
    }

    {
        std::string str = "0 + 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 + 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "0 + 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "1 + 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 2.0f);
    }
    {
        std::string str = "222 + 333 + 444";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 999.0f);
    }
    {
        std::string str = "222.002 + 333.005 + 444.001";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 999.01f);   // Round 2
        EXPECT_NE(testGetRes(), 999.008f);
    }    
    {
        std::string str = "0.001 + 0.001 + 0.001 + 0.0005 + 0.0005 + 0.0005 + 0.00025 + 0.00025";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.01f);
        EXPECT_NE(testGetRes(), 0.00f);
    }    
    {
        std::string str = "0.001 + 0.001 + 0.001 + 0.0005 + 0.0005 + 0.0005 + 0.00025 + 0.00024";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_NE(testGetRes(), 0.01f);
        EXPECT_EQ(testGetRes(), 0.00f);
    }    
    {
        std::string str = "10000000";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10000000.0f);
    }    
    {
        std::string str = "1";
        for (int i = 0; i < 9999999; ++i) str += " + 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10000000.0f);
    }    
}


TEST(CalculatorTest, SubTest) {
    {
        std::string str = "-";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "0 - 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 - 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "0 - 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -1.0f);
    }
    {
        std::string str = "1 - 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1.05 - 0.05";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);   
    }   
    {
        std::string str = "0 - 5 - 1 - 2 - 3 - 4";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -15.0f); 
    }   
    {
        std::string str = "500 - 100.01 - 800 + 800 + 100.02";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 500.01f);
    }
}


TEST(CalculatorTest, UnaryTest) {
    {
        std::string str = "1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "+1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "-1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -1.0f);
    }
    {
        std::string str = "++1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "--1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "+++1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "---1";
        EXPECT_FALSE(testCalcStr(str));
    }
        {
        std::string str = "+1+";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "-1-";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1+";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1-";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1++";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1--";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1+++";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1---";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "+-1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "-+1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "*1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "/1";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1/";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1*";
        EXPECT_FALSE(testCalcStr(str));
    }
}


TEST(CalculatorTest, MulTest) {
    {
        std::string str = "*";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "0 * 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 * 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "0 * 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 * 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "1 * 5.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 5.0f);   
    }   
    {
        std::string str = "5.8 * (-1.0)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -5.8f); 
    }   
    {
        std::string str = "-5.8 * (-1.0)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 5.8f); 
    }   
    {
        std::string str = "4 * 0.25";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f); 
    }   
    {
        std::string str = "10 * 10 * 10 * 10 * 10 * 10 * 10";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10000000.0f);
    }    
    {
        std::string str = "(10 * 10) * 10 * (10 * 10) * 10 * 10";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10000000.0f);
    }    
}


TEST(CalculatorTest, DivTest) {
    {
        std::string str = "/";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "0 / 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_TRUE(std::isnan(testGetRes()));
    }
    {
        std::string str = "1 / 0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_TRUE(std::isinf(testGetRes()));
    }
    {
        std::string str = "0 / 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 / 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }
    {
        std::string str = "1 / 5.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.2f);   
    }   
    {
        std::string str = "5.8 / (-1.0)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -5.8f); 
    }   
    {
        std::string str = "-5.8 / (-1.0)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 5.8f); 
    }   
    {
        std::string str = "4 / 0.25";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 16.0f); 
    }   
    {
        std::string str = "10000000 / 10 / 10 / 10 / 10 / 10 / 10 / 10";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }    
    {
        std::string str = "10000000 / 10 / (10 / 10) / ((10 / 10) / 10)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10000000.0f);
    }    
}


TEST(CalculatorTest, DotTest) {
    {
        std::string str = "1.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }    
    {
        std::string str = "1,0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }    
    {
        std::string str = "1,,0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = "1..0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = "1.05.0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = "1,05,0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = "1,05.0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = "1.05,0";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = ".0";
        EXPECT_FALSE(testCalcStr(str));
    }    
    {
        std::string str = ",0";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = ".0.1";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = ",0,1";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = ".0,1";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = ",0.1";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "0.1.";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "0,1,";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "0.1,";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "0,1.";
        EXPECT_FALSE(testCalcStr(str));
    }   
}


TEST(CalculatorTest, BracketsTest) {
    {
        std::string str = "(";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = ")";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "()";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "((()))";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "(1 + 1)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 2.0f);
    }
    {
        std::string str = "1 + 1)";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "(1 + (-1))";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 0.0f);
    }
    {
        std::string str = "1 + 1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 2.0f);
    }
    {
        std::string str = "1 + 1 + (2 + 2";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "1 + 1 + (2 + 2)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 6.0f);
    }
    {
        std::string str = "2 * 1 + 5";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 7.0f);
    }
    {
        std::string str = "(2 * 1) + 5";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 7.0f);
    }
    {
        std::string str = "2 * (1 + 5)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 12.0f);
    }
    {
        std::string str = "1 + 5 * 2";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 11.0f);
    }
    {
        std::string str = "(1 + 5) * 2";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 12.0f);
    }
    {
        std::string str = "1 + (5 * 2)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 11.0f);
    }
    {
        std::string str = "2 * (-2 + 4) / 0,5 + 10";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 18.0f);
    }
    
}


TEST(CalculatorTest, SpaceTest) {
    {
        std::string str = "-1.0 + 2.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "-1.0+2.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "-1.0+     2.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "-   1.0      +  2.0         ";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "-                      1.0 + 2.0";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "-1.0                + 2.0                  ";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "           -          1.0                               +          2.0              ";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
}


TEST(CalculatorTest, FormatTest) {
    {
        std::string str = "1.0000000000000000";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "0000000000000000001.0000000000000000";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }   
    {
        std::string str = "0000000000000010001,05000000000000000000000000000000000000";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 10001.05f);
    }   
    {
        std::string str = "0000000000000010001.05000000000000000000000000000000000000f";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "1 + abs";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "8d1 + 500";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "8'b00000000";
        EXPECT_FALSE(testCalcStr(str));
    }   
    {
        std::string str = "1e+08";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "o";
        EXPECT_FALSE(testCalcStr(str));
    }      
    {
        std::string str = "1 + 815 / 416 * 919.5 - 7^2";
        EXPECT_FALSE(testCalcStr(str));
    }      
}


TEST(CalculatorTest, ForwardTest1) {
    {
        std::string str = "1";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1.0f);
    }      
    {
        std::string str = "1000.05";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1000.05f);
    }      
    {
        std::string str = "1.05 + ";
        EXPECT_FALSE(testCalcStr(str));
    }      
    {
        std::string str = "1.05 + 2";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }      
    {
        std::string str = "(1.05 + 2";
        EXPECT_FALSE(testCalcStr(str));
    }      
    {
        std::string str = "(1.05 + 2)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }      
    {
        std::string str = "(1.05 + 2) (";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * (";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * ()";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * (/)";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * (500/)";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * (/500.000000)";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "(1.05 + 2) * (500/500.000000)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }    
    {
        std::string str = "((1.05 + 2) * (500/500.000000))";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }    
    {
        std::string str = "((1.05 + 2) * (500/500.000000)) /";
        EXPECT_FALSE(testCalcStr(str));
    }     
    {
        std::string str = "((1.05 + 2) * (500/500.000000)) /                 000000001.0000000000000000000000000000000";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }    
    {
        std::string str = "((1.05 + 2) * (500/500.000000)) / 1)";
        EXPECT_FALSE(testCalcStr(str));
    }
    {
        std::string str = "((((1.05 + 2) * (500/500.000000)) / 1)";
        EXPECT_FALSE(testCalcStr(str));
    }       
    {
        std::string str = "(((1,05 + 2) * (500/500.000000)) / 1)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.05f);
    }     
    {
        std::string str = "0.002(((1.05 + 2) * (500/500.000000)) / 1)";
        EXPECT_FALSE(testCalcStr(str));
    } 
    {
        std::string str = "0.002-(((1.05 + 2) * (500/500.000000)) / 1)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), -3.05f);
    }         
    {
        std::string str = "0.002-(((1,05 + 2) * (500/500.000000)) / 1) +7";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 3.95f);
    }            
}


TEST(CalculatorTest, MaleExamplesTest) {
    {
        std::string str = "-1 + 5 - 3";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 1);
    }  
    {
        std::string str = "-10 + (8 * 2.5) - (3 / 1,5)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 8);
    }  
    {
        std::string str = "1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)";
        EXPECT_TRUE(testCalcStr(str));
        EXPECT_EQ(testGetRes(), 11);
    }  
    {
        std::string str = "1.1 + 2.1 + abc";
        EXPECT_FALSE(testCalcStr(str));
    }  
}