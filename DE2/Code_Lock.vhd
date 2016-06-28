----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Code_Lock is
	port(	clk, reset, codeEntry	: in std_logic;
			code							: in std_logic_vector(16 downto 1); --Skal også ændres i FullTester (linje 15) og Receiver (linje 7 og 16)
			lock							: out std_logic
			--bitsPerCode					: in natural
			);
end Code_Lock;

architecture simple of Code_Lock is
type state is (idle, eval, going_idle);
signal present_state, next_state : state;

begin
state_reg: process(clk, reset)	-- reset and clocking to next state
begin
	if reset = '0' then
		present_state <= idle;
	elsif rising_edge(clk) then
		present_state <= next_state;
	end if;
end process;

nxt_state: process(present_state, codeEntry)	-- State Machine transitions
begin
	next_state <= present_state;
	case present_state is
		when idle =>
			if codeEntry = '1' then				-- her vi læser normalt
				next_state <= eval;
			end if;
		when eval =>
			if (codeEntry = '0') then
				next_state <= going_idle;
			end if;
		when going_idle =>
			next_state <= idle;
		when others =>
			next_state <= idle;
	end case;
end process;

outputs: process(present_state)	-- State machine output
begin
	case present_state is
		when eval =>
			if (code(16 downto 9) = code(8 downto 1)) then
				lock <= '1';
			else
				lock <= '0';
			end if;
		when others =>
			null;
		end case;
end process;

end simple;