----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BaudRateGenerator is
	port (	clk, reset	: in std_logic;
			clk_baud	: out std_logic
				);
end BaudRateGenerator;

architecture Gen57600 of BaudRateGenerator is
begin

process(clk, reset)
variable clk_count : integer := 0;
begin
	if (reset = '0') then
		clk_count := 0;
	elsif (rising_edge(clk)) then
		clk_count := clk_count + 1;
	else
		null;
	end if;
	case clk_count is
		when 1302 => --For real test	//20832/16=1302
		--when 19 =>	-- For simulation
			clk_baud <= '1';
		when 1303 =>	--For real test	//1302+1
		--when 20 =>	-- For simulation
			clk_count := 0;
		when others =>
			clk_baud <= '0';
			--null;
	end case;
end process;

end Gen57600;