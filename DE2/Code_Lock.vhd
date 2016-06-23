----- Libraries -----
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Code_Lock is
	port(	clk, reset, codeEntry	: in std_logic;
			code							: in std_logic_vector(16 downto 1); --Skal også ændres i FullTester (linje 15) og Receiver (linje 7 og 16)
			lock,clk_out				: out std_logic
			);
end Code_Lock;

architecture simple of Code_Lock is
type state is (idle, eval, going_idle);
constant end_length : natural := 16;	--Skal også ændres i FullTester (linje 15), Code_Lock (linje 8) og her (linje 7 og 16)

signal present_state, next_state : state;
--variable clk_cnt	: integer range 0 to 15;
--variable clk_out_var : std_logic := '0';
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
variable cnt : integer range 0 to 15 := 7;
variable clk_out_var : std_logic := '0';
begin
clk_out_var := '0';
	next_state <= present_state;
	case present_state is
		when idle =>
			if codeEntry = '1' then				-- her vi læser normalt
				if cnt = 15 then
					next_state <= eval;
					cnt := 0;
					clk_out_var := '1';
				else
					cnt := cnt + 1;
				end if;				
			end if;
		when eval =>
			if codeEntry = '0' then
				next_state <= going_idle;
			end if;
		when going_idle =>
			cnt := 7;
			next_state <= idle;			
		when others =>
			next_state <= idle;
	end case;
	clk_out <= clk_out_var;
end process;

outputs: process(present_state)	-- State machine output
begin
	case present_state is
		when eval =>
			--if code(end_length downto (end_length/2 + 1)) = code(end_length/2 downto 1) then
			if (code(16 downto 9) = code(8 downto 1)) then
				lock <= '1';
			else
				lock <= '0';
			end if;
		when others =>
			lock <= '0';
		end case;
end process;

end simple;