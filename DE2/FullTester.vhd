----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;

entity FullTester is
	port (	CLOCK_50	: in std_logic;
				KEY		: in std_logic_vector(0 downto 0);
				GPIO_0	: in std_logic_vector(0 downto 0);
				GPIO_1	: out std_logic_vector(1 downto 0);
				LEDR		: out std_logic_vector(17 downto 0);
				LEDG		: out std_logic_vector(7 downto 0)
	);
end FullTester;

architecture test of FullTester is
signal clk_57600, recvalid 	: std_logic := '0';	-- recvalid er det 1 eller 0 fra rxvalid, som checker om vi har fået en korrekt string.
signal reset_baud_out		: std_logic := '1';
--signal indata				: std_logic_vector(128 downto 1) := (others => '0'); --Skal også ændres i Code_Lock (linje 8) og Receiver (linje 7 og 16)
signal indata								: std_logic_vector(16 downto 1) := (others => '0');
begin
gen			: entity work.BaudRateGenerator		port map (	clk => CLOCK_50, reset => reset_baud_out, clk_baud => clk_57600);
rec			: entity work.Receiver				port map (	rxd => GPIO_0(0), reset => KEY(0), clk_baud => clk_57600, rxdata => indata, rxvalid => recvalid);
codelock	: entity work.Code_Lock				port map (	clk => CLOCK_50, reset => KEY(0), codeEntry => recvalid, code => indata, lock => GPIO_1(0), reset_baud => reset_baud_out);
GPIO_1(1) <= clk_57600;
--LEDG <= indata(8 downto 1);
LEDR(15 downto 0) <= indata(16 downto 1);
process(recvalid, KEY(0))
begin
	if (KEY(0) = '0') then
		LEDR(17) <= '0';
	elsif (recvalid = '1' AND (indata(16 downto 9) = indata(8 downto 1))) then
		LEDR(17)	<= '1';
	else
		LEDR(17) <= '0';
	end if;
end process;

end test;