----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity BaudRateGenerator is
	port (	clk, reset	: in std_logic;
				clk_baud		: out std_logic
				);
end BaudRateGenerator;

architecture Gen57600 of BaudRateGenerator is
begin

process(clk, reset)
variable clk_count : integer;
begin
	if reset = '0' then
		clk_count := 0;
	elsif rising_edge(clk) then
		clk_count := clk_count + 1;
	else
		null;
	end if;
	case clk_count is
		when 867 => --For real test
		--when 49 =>	-- For simulation
			clk_baud <= '1';
		when 868 =>	--For real test
		--when 50 =>	-- For simulation
			clk_count := 0;
		when others =>
		clk_baud <= '0';
	end case;
end process;

end Gen57600;