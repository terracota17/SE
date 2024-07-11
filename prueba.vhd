----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    15:31:57 10/03/2013 
-- Design Name: 
-- Module Name:    prueba - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity prueba is
    Port ( in1 : in  STD_LOGIC;
           in2 : in  STD_LOGIC;
			  clk: in STD_LOGIC;
           salida : out  STD_LOGIC;
			  salida2:  out  STD_LOGIC);
end prueba;

architecture Behavioral of prueba is
component divisor1 is 
    port (
        rst: in STD_LOGIC;
        clk_in: in STD_LOGIC;
        clk_out: out STD_LOGIC
    );
end component;
signal clk_out: std_logic;
begin
divis: divisor1
PORT MAP(rst => '0',
	clk_in =>  clk,
	clk_out => clk_out);
salida <= in1 and in2;
salida2<= clk_out;
end Behavioral;

